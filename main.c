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
#include "revere_dev.h"
#include "revere_hw.h"
#include "platform.h"

/* The i/o virtual address for our buffers, as seen from Revere.
 * This needs to be a multiple of 4KB.
 * In this demo we do not allow a zero IOVA to help debug. */
#define IOVA 0x42000

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

	memset(p, 0xde, size);
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
	struct cmdline cl;
	struct revere_dev rd;
	uint8_t pci_command;
	int i;
	uint64_t write_index_tx0, read_index_rx0;
	unsigned slot_doublewords;
	struct platform plat;
	struct revere_buffers *bufs;

	parse_cmdline(&cl, argc, argv);
	slot_doublewords = 1 << cl.log2_msg_length;

	// Allocate our i/o buffers
	size = round_to_pgsize(sizeof(struct revere_buffers));
	bufs = allocate_buffers(size);

	/* Setup the platform.
	 * With VFIO, open the device and map memory into Revere IOVA space
	 * Also, map BAR0 into our process address space and turn on BME. */
	setup(&plat, &cl);
	map_dma(&plat, bufs, size, IOVA);
	pci_command = read_config(&plat, PCI_COMMAND);
	write_config(&plat, PCI_COMMAND, pci_command | PCI_COMMAND_MASTER);

	/* Setup the Revere device.
	 * This will setup the management interface.
	 * Then using the management interface, this will setup an AMI-SW.
	 * By default it will also setup AMI-HWs in the accelerator and connect
	 * them with sessions. Otherwise when in loopback mode, only the AMI-SW
	 * is setup and connected. */
	revere_dev_setup(&rd, bufs, &plat, IOVA, &cl);

	/* Exchange some data through Revere messages. By default this is with
	 * the inversion agent, and we verify that data has indeed been
	 * inverted. In loopback mode there is no inversion. */
	write_index_tx0 = readq(&plat, AMI_SW0 + WRITE_INDEX_TX0);
	read_index_rx0 = readq(&plat, AMI_SW0 + READ_INDEX_RX0);

	for (i = 0; i < cl.packets; i++) {
		uint8_t *q;
		unsigned int slot;
		int j;
		uint64_t read_index_tx0, write_index_rx0;

		printf("%d ", i);

		// Check that Tx is empty
		read_index_tx0 = readq(&plat, AMI_SW0 + READ_INDEX_TX0);

		if (!ring_is_empty(read_index_tx0, write_index_tx0))
			errx(1, "non empty tx");

		// Enqueue data in the slot
		slot = write_index_tx0 & RING_SLOTS_MASK;
		q = (uint8_t *)&rd.bufs->tx[slot * slot_doublewords];

		for (j = 0; j < (int)slot_doublewords * 8; j++)
			q[j] = (i + j);

		// Advance write index and notify Revere
		write_index_tx0++;
		writeq(&plat, write_index_tx0, AMI_SW0 + WRITE_INDEX_TX0);

		// Wait for an Rx slot
		for (j = 0; j < cl.timeout; j++) {
			write_index_rx0 = readq(&plat, AMI_SW0 +
							WRITE_INDEX_RX0);

			if (!ring_is_empty(read_index_rx0, write_index_rx0))
				break;

			msleep(&plat);
		}

		if (j >= cl.timeout)
			errx(1, "rx timeout");

		// Verify received data
		slot = read_index_rx0 & RING_SLOTS_MASK;
		q = (uint8_t *)&rd.bufs->rx[slot * slot_doublewords];

		for (j = 0; j < (int)slot_doublewords * 8; j++) {
			uint8_t x = (i + j);

			// We expect inverted data only in default mode
			if (!cl.loopback)
				x = ~x;

			if (q[j] != x) {
				errx(1, "unexpected data %d != %d at byte %d",
					q[j], x, j);
			}
		}

		// Notify Revere that we have dequeued the data
		read_index_rx0++;
		writeq(&plat, read_index_rx0, AMI_SW0 + READ_INDEX_RX0);
		fflush(NULL);
	}

	printf("\n");

	// Teardown everything and exit
	revere_dev_teardown(&rd);
	pci_command = read_config(&plat, PCI_COMMAND);
	write_config(&plat, PCI_COMMAND, pci_command & ~PCI_COMMAND_MASTER);
	teardown(&plat);
	free_buffers(rd.bufs, size);
	printf("Done.\n");
	return 0;
}
