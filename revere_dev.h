/* SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright (C) 2018-2019 Arm Ltd.
 * Author: Vincent Stehlé <vincent.stehle@arm.com>
 */

#ifndef REVERE_DEV_H_INCLUDED
#define REVERE_DEV_H_INCLUDED

#include <stdint.h>

/* Management rings size */
#define MGT_SLOT_DOUBLEWORDS_POT	3
#define MGT_SLOT_DOUBLEWORDS		(1 << MGT_SLOT_DOUBLEWORDS_POT)

/* Ring slot size */
#define RING_SLOT_DOUBLEWORDS_POT	(11 - 3)
#define RING_SLOT_DOUBLEWORDS		(1 << RING_SLOT_DOUBLEWORDS_POT)
#define RING_SLOTS_POT	6
#define RING_SLOTS		(1 << RING_SLOTS_POT)
#define RING_SLOTS_MASK		(RING_SLOTS - 1)

// A structure to contain all our i/o buffers, which are shared with Revere
struct revere_buffers {
	uint64_t cmd[MGT_SLOT_DOUBLEWORDS];
	uint64_t resp[MGT_SLOT_DOUBLEWORDS];
	uint64_t exc[MGT_SLOT_DOUBLEWORDS];
	uint64_t tx[RING_SLOTS * RING_SLOT_DOUBLEWORDS];
	uint64_t rx[RING_SLOTS * RING_SLOT_DOUBLEWORDS];
};

struct revere_dev {
	struct revere_buffers *bufs;
	void *regs;
	uint64_t iova;
};

void revere_dev_setup(struct revere_dev *rd);
void revere_dev_teardown(struct revere_dev *rd);

static inline int ring_is_empty(uint64_t read_index, uint64_t write_index)
{
	return read_index == write_index;
}

#endif /* REVERE_DEV_H_INCLUDED */
