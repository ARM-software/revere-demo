/* SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright (C) 2018-2019 Arm Ltd.
 * Author: Vincent Stehlé <vincent.stehle@arm.com>
 */

#ifndef CMDLINE_H_INCLUDED
#define CMDLINE_H_INCLUDED

struct cmdline {
	char *opt_vfio_group;
	char *opt_device;
};

void usage(const char *argv0);
void parse_cmdline(struct cmdline *cl, int argc, char *const argv[]);

#endif // CMDLINE_H_INCLUDED
