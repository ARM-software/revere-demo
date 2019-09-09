/* SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright (C) 2018-2019 Arm Ltd.
 * Author: Vincent Stehlé <vincent.stehle@arm.com>
 */

#include "cmdline.h"
#include <getopt.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const struct option long_options[] = {
	{"help",		no_argument,		0, 'h'},
	{"vfio-group",		required_argument,	0, 'g'},
	{"device",		required_argument,	0, 'd'},
	{0, 0, 0, 0}
};

/* Print usage (but do not exit) */
void usage(const char *argv0)
{
	const struct option *p;

	assert(argv0);

	printf("Usage: %s [options]\n", argv0);
	printf("Options in:\n");

	for (p = long_options; p->name; p++) {
		printf("\t-%c, --%s", p->val, p->name);

		if (p->has_arg == required_argument)
			printf("\t<arg>");

		printf("\n");
	}

	printf("\n");
}

/* Compute short option string */
static void compute_optstring(char *p, size_t s)
{
	const struct option *o;
	unsigned i;

	for (o = long_options, i = 0; o->name && i < s; o++) {
		p[i++] = o->val;

		if (o->has_arg == required_argument && i < s)
			p[i++] = ':';
	}

	p[i] = '\0';
}

/** Parse command line
 * This function uses getopt_long(), which sets optind.
 * \param[in]	argc, argv	Standard parameters from main()
 */
void parse_cmdline(struct cmdline *cl, int argc, char *const argv[])
{
	char optstring[64];

	assert(cl);
	assert(argc);
	assert(argv);

	memset(cl, 0, sizeof(*cl));
	compute_optstring(optstring, sizeof(optstring));

	while (1) {
		int c;

		/* getopt_long stores the option index here. */
		int option_index = 0;

		c = getopt_long(argc, argv, optstring, long_options, &option_index);

		/* Detect the end of the options. */
		if (c == -1)
			break;

		switch (c) {
		case 'd':
			cl->opt_device = optarg;
			break;

		case 'g':
			cl->opt_vfio_group = optarg;
			break;

		case 'h':
			usage(argv[0]);
			exit(0);
			break;

		case '?':
			/* getopt_long already printed an error message. */
			usage(argv[0]);
			exit(1);
			break;

		default:
			/* Unhandled; getopt_long already printed an error message. */
			usage(argv[0]);
			exit(1);
			break;
		}
	}

	if (!cl->opt_vfio_group || !cl->opt_device) {
		fprintf(stderr, "I need a group and a device\n");
		usage(argv[0]);
		exit(1);
	}
}
