/* SPDX-License-Identifier: BSD-3-Clause
 *
 * Arm Revere VFIO demo
 *
 * Copyright (C) 2018-2019 Arm Ltd.
 * Author: Vincent Stehlé <vincent.stehle@arm.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <sys/mman.h>
#include <linux/pci_regs.h>
#include <string.h>
#include <unistd.h>
#include "cmdline.h"
#include "vfio.h"
#include "revere_dev.h"
#include "revere_hw.h"

/* The i/o virtual address for our buffers, as seen from Revere.
 * This needs to be a multiple of 4KB. */
#define IOVA 0x42000

// Polling timeout
#define POLL_MS	100

// Round up to the next multiple of 4KB
static size_t round_to_pgsize(size_t size)
{
	const size_t pgsize = 0x1000;
	const size_t pgmask = pgsize - 1;

	return (size + pgmask) & ~pgmask;
}

// Allocate our i/o buffers
static void *allocate_buffers(size_t size)
{
	void *p = mmap(0, size, PROT_READ | PROT_WRITE,
			 MAP_SHARED | MAP_ANONYMOUS | MAP_POPULATE, -1, 0);
	if (!p)
		err(1, "mmap failed");

	return p;
}

static void free_buffers(void *p, size_t size)
{
	int s = munmap(p, size);
	if (s)
		warn("munmap: %d", s);
}

int main(int argc, char *argv[])
{
	size_t size;
	struct vfio v;
	struct cmdline cl;
	struct revere_dev rd = {
		.iova = IOVA,
	};
	uint8_t pci_command;
	int i;
	void *ami0;
	uint64_t write_index_tx0, read_index_rx0;

	parse_cmdline(&cl, argc, argv);

	// Allocate our i/o buffers
	size = round_to_pgsize(sizeof(struct revere_buffers));
	rd.bufs = allocate_buffers(size);

	/* Open the device with VFIO and map memory into Revere IOVA space
	 * Also, map BAR0 into our process address space and turn on BME. */
	vfio_setup(&v, cl.opt_vfio_group, cl.opt_device);
	vfio_map_dma(&v, rd.bufs, size, rd.iova);
	rd.regs = vfio_map_bar0(&v);
	pci_command = vfio_read_config(&v, PCI_COMMAND);
	vfio_write_config(&v, PCI_COMMAND, pci_command | PCI_COMMAND_MASTER);

	/* Setup the Revere device.
	 * This will setup the management interface.
	 * Then using the management interface, this will setup the AMI-HWs in
	 * the accelerator, an AMI-SW and it will connect them with sessions */
	revere_dev_setup(&rd);

	/* Exchange data with the inversion agent and verify that it has
	 * been inverted */
	ami0 = (void *)((uintptr_t)rd.regs + RVR_AMI_SW_PAGE_0_OFFSET);
	write_index_tx0 = revere_readq(ami0, WRITE_INDEX_TX0);
	read_index_rx0 = revere_readq(ami0, READ_INDEX_RX0);

	for (i = 0; i < 42; i++) {
		uint64_t *p;
		char *q;
		unsigned int slot;
		int j, s;
		uint64_t read_index_tx0, write_index_rx0;

		printf("%d ", i);

		// Check that Tx is empty
		read_index_tx0 = revere_readq(ami0, READ_INDEX_TX0);
		if (!ring_is_empty(read_index_tx0, write_index_tx0))
			errx(1, "non empty tx");

		// Enqueue data in the slot
		slot = write_index_tx0 & RING_SLOTS_MASK;
		p = &rd.bufs->tx[slot * RING_SLOT_DOUBLEWORDS];
		memset(p, i, RING_SLOT_DOUBLEWORDS * sizeof(uint64_t));

		// Advance write index and notify Revere
		write_index_tx0++;
		revere_writeq(ami0, write_index_tx0, WRITE_INDEX_TX0);

		// Wait for an Rx slot
		for (j = 0; j < POLL_MS; j++) {
			write_index_rx0 = revere_readq(ami0, WRITE_INDEX_RX0);

			if (!ring_is_empty(read_index_rx0, write_index_rx0))
				break;

			s = usleep(1000);
			if (s < 0)
				err(1, "usleep: %d", s);
		}

		if (j >= POLL_MS)
			errx(1, "rx timeout");

		// Verify received data
		slot = read_index_rx0 & RING_SLOTS_MASK;
		q = (char *)&rd.bufs->rx[slot * RING_SLOT_DOUBLEWORDS];

		for (j = 0; j < (int)(RING_SLOT_DOUBLEWORDS * sizeof(uint64_t));
			j++)
		{
			uint8_t inv = ~i;

			if (q[j] != inv) {
				errx(1, "unexpected data %d != %d at byte %d",
					q[j], inv, j);
			}
		}

		// Notify Revere that we have dequeued the data
		read_index_rx0++;
		revere_writeq(ami0, read_index_rx0, READ_INDEX_RX0);
	}

	printf("\n");

	// Teardown everything and exit
	revere_dev_teardown(&rd);
	pci_command = vfio_read_config(&v, PCI_COMMAND);
	vfio_write_config(&v, PCI_COMMAND, pci_command & ~PCI_COMMAND_MASTER);
	vfio_teardown(&v);
	free_buffers(rd.bufs, size);
	printf("Done.\n");
	return 0;
}
