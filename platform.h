/* SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright (C) 2018-2019 Arm Ltd.
 * Author: Vincent Stehlé <vincent.stehle@arm.com>
 */

#ifndef PLATFORM_H_INCLUDED
#define PLATFORM_H_INCLUDED

#include <stdlib.h>
#include <stdint.h>
#include "cmdline.h"

/*
 * Every platform must implement the following:
 *
 * struct platform;
 * void setup(struct platform *p, const struct cmdline *cl);
 * void map_dma(struct platform *p, void *bufs, size_t size, uint64_t iova);
 * uint8_t read_config(struct platform *p, unsigned int off);
 * void write_config(struct platform *p, unsigned int off, uint8_t val);
 * uint64_t readq(struct platform *p, unsigned int offset);
 * void writeq(struct platform *p, uint64_t value, unsigned int offset);
 * void msleep(struct platform *p);
 * void teardown(struct platform *p);
 */

#include "config.h"

#ifdef VFIO
#include <unistd.h>
#include <err.h>
#include "vfio.h"
#include "regs.h"

struct platform {
	struct vfio v;
	void *bar0;
};

void setup(struct platform *p, const struct cmdline *cl);
void msleep(struct platform *p);
void teardown(struct platform *p);

static inline void map_dma(struct platform *p, void *bufs, size_t size,
				uint64_t iova)
{
	vfio_map_dma(&p->v, bufs, size, iova);
}

static inline uint8_t read_config(struct platform *p, unsigned int off)
{
	return vfio_read_config(&p->v, off);
}

static inline void write_config(struct platform *p, unsigned int off,
					uint8_t val)
{
	vfio_write_config(&p->v, off, val);
}

static inline uint64_t readq(struct platform *p, unsigned int offset)
{
	return regs_readq(p->bar0, offset);
}

static inline void writeq(struct platform *p, uint64_t value,
				unsigned int offset)
{
	regs_writeq(p->bar0, value, offset);
}
#endif // VFIO

#endif // PLATFORM_H_INCLUDED
