/* SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright (C) 2018-2019 Arm Ltd.
 * Author: Vincent Stehlé <vincent.stehle@arm.com>
 */

#ifndef CMDLINE_H_INCLUDED
#define CMDLINE_H_INCLUDED

#include <stdbool.h>
#include "config.h"

struct cmdline {
	bool loopback;
	bool dma;
	int aha;
	int log2_msg_length;
	int packets;
	int rx_ami_hw;
	int timeout;	// In ms.
	int tx_ami_hw;
#ifdef VFIO
	char *device;
	char *vfio_group;
#endif
};

void parse_cmdline(struct cmdline *cl, int argc, char *const argv[]);

#endif // CMDLINE_H_INCLUDED
