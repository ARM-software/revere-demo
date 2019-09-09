/* SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright (C) 2018-2019 Arm Ltd.
 * Author: Vincent Stehlé <vincent.stehle@arm.com>
 */

#ifndef REVERE_DEV_H_INCLUDED
#define REVERE_DEV_H_INCLUDED

#include <stdint.h>
#include <stdbool.h>
#include "cmdline.h"
#include "platform.h"

/* Management rings size */
#define MGT_SLOT_DOUBLEWORDS_POT	3
#define MGT_SLOT_DOUBLEWORDS		(1 << MGT_SLOT_DOUBLEWORDS_POT)

/* Ring slot size */
#define MAX_RING_SLOT_DOUBLEWORDS_POT	(11 - 3)
#define MAX_RING_SLOT_DOUBLEWORDS	(1 << MAX_RING_SLOT_DOUBLEWORDS_POT)
#define RING_SLOTS_POT	6
#define RING_SLOTS		(1 << RING_SLOTS_POT)
#define RING_SLOTS_MASK		(RING_SLOTS - 1)

/*
 * A structure to contain all our i/o buffers, which are shared with Revere
 * We allocate for the maximum slot size, but the actual slot size is specified
 * with a command line option.
 * On ALP 03, hardware support is verified at runtime.
 * TODO! Alignment
 */
struct revere_buffers {
	uint64_t cmd[MGT_SLOT_DOUBLEWORDS];
	uint64_t resp[MGT_SLOT_DOUBLEWORDS];
	uint64_t exc[MGT_SLOT_DOUBLEWORDS];
	uint64_t tx[RING_SLOTS * MAX_RING_SLOT_DOUBLEWORDS];
	uint64_t rx[RING_SLOTS * MAX_RING_SLOT_DOUBLEWORDS];
};

struct revere_dev {
	struct revere_buffers *bufs;
	struct platform *plat;
	uint64_t iova;
	const struct cmdline *cl;
	unsigned phy_ami_sw;
};

void revere_dev_setup(struct revere_dev *rd, struct revere_buffers *bufs,
			struct platform *plat, uint64_t iova,
			const struct cmdline *cl);

void revere_dev_teardown(struct revere_dev *rd);

static inline int ring_is_empty(uint64_t read_index, uint64_t write_index)
{
	return read_index == write_index;
}

#endif /* REVERE_DEV_H_INCLUDED */
