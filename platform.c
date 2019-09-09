/* SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright (C) 2018-2019 Arm Ltd.
 * Author: Vincent Stehlé <vincent.stehle@arm.com>
 */

#include "platform.h"
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include "cmdline.h"
#include "config.h"

#ifdef VFIO
#include <unistd.h>
#include <err.h>
#include "vfio.h"
#include "regs.h"

void setup(struct platform *p, const struct cmdline *cl)
{
	assert(p);
	assert(cl);

	vfio_setup(&p->v, cl);
	p->bar0 = vfio_map_bar0(&p->v);
}

void msleep(struct platform *p)
{
	int s;

	assert(p);
	(void)p;

	s = usleep(1000);
	if (s < 0)
		err(1, "usleep: %d", s);
}

void teardown(struct platform *p)
{
	assert(p);

	vfio_teardown(&p->v);
#ifndef NDEBUG
	memset(p, 0, sizeof(*p));
#endif
}
#endif // VFIO
