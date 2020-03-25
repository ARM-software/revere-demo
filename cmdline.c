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
#include "revere_dev.h"
#include "config.h"

static const struct option long_options[] = {
	{"aha",			required_argument,	0, 'a'},
	{"help",		no_argument,		0, 'h'},
	{"log2-msg-length",	required_argument,	0, 'L'},
	{"loopback",		no_argument,		0, 'l'},
	{"dma",         no_argument,    0, 'm'},
	{"packets",		required_argument,	0, 'p'},
	{"rx-ami-hw",		required_argument,	0, 'r'},
	{"timeout",		required_argument,	0, 'T'},
	{"tx-ami-hw",		required_argument,	0, 't'},
#ifdef VFIO
	{"device",		required_argument,	0, 'd'},
	{"vfio-group",		required_argument,	0, 'g'},
#endif
	{0, 0, 0, 0}
};

/* Print options values */
static void print_opts(const struct cmdline *cl)
{
	printf("Current options values:\n");
	printf("  aha: %d, ami-hw rx: %d, tx: %d\n", cl->aha, cl->rx_ami_hw,
		cl->tx_ami_hw);
	printf("  loopback: %d\n", cl->loopback);
	printf("  dma: %d\n", cl->dma);
	printf("  log2-msg-length: %d (%d B)\n", cl->log2_msg_length,
		8 << cl->log2_msg_length);
	printf("  packets: %d\n", cl->packets);
	printf("  timeout: %d ms\n", cl->timeout);

#ifdef VFIO
	printf("  device: `%s', vfio group: `%s'\n", cl->device,
		cl->vfio_group);
#endif
}

/* Print usage (but do not exit) */
static void usage(const char *argv0, struct cmdline *cl)
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
	print_opts(cl);
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

	assert(i < s);
	p[i] = '\0';
}

/** Parse command line
 * This function uses getopt_long(), which sets optind.
 * \param[in]	argc, argv	Standard parameters from main()
 */
void parse_cmdline(struct cmdline *cl, int argc, char *const argv[])
{
	char optstring[128];

	assert(cl);
	assert(argc);
	assert(argv);

	// Default values
	*cl = (struct cmdline){
		.aha = 0,
		.log2_msg_length = MAX_RING_SLOT_DOUBLEWORDS_POT,
		.packets = 42,
		.timeout = 100,	// In ms.
		.tx_ami_hw = 0,
#ifdef VFIO
		.device = "0000:00:01.0",
		.vfio_group = "/dev/vfio/0",
#endif
	};

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
		case 'h':
			usage(argv[0], cl);
			exit(0);
			break;

		case 'L': cl->log2_msg_length = atoi(optarg); break;
		case 'T': cl->timeout = atoi(optarg); break;
		case 'a': cl->aha = atoi(optarg); break;
		case 'l': cl->loopback = true; break;
		case 'm': cl->dma = true; break;
		case 'p': cl->packets = atoi(optarg); break;
		case 'r': cl->rx_ami_hw = atoi(optarg); break;
		case 't': cl->tx_ami_hw = atoi(optarg); break;

#ifdef VFIO
		case 'd': cl->device = optarg; break;
		case 'g': cl->vfio_group = optarg; break;
#endif

		case '?':
			/* getopt_long already printed an error message. */
			usage(argv[0], cl);
			exit(1);
			break;

		default:
			/* Unhandled; getopt_long already printed an error message. */
			usage(argv[0], cl);
			exit(1);
			break;
		}
	}

	if (cl->aha < 0) {
		fprintf(stderr, "AHA must be >= 0\n");
		goto err;
	}

	if (cl->tx_ami_hw < 0) {
		fprintf(stderr, "Tx AMI-HW must be >= 0\n");
		goto err;
	}

	if (cl->rx_ami_hw < 0) {
		fprintf(stderr, "Rx AMI-HW must be >= 0\n");
		goto err;
	}

	if (cl->timeout < 0) {
		fprintf(stderr, "Timeout must be >= 0\n");
		goto err;
	}

	if (cl->log2_msg_length < 0) {
		fprintf(stderr, "Log2 msg length must be >= 0\n");
		goto err;
	}

	if (cl->log2_msg_length > MAX_RING_SLOT_DOUBLEWORDS_POT) {
		fprintf(stderr, "Log2 msg length must be <= %d\n",
			MAX_RING_SLOT_DOUBLEWORDS_POT);
		goto err;
	}

	if (cl->packets < 0) {
		fprintf(stderr, "Packets must be >= 0\n");
		goto err;
	}

#ifdef VFIO
	if (!cl->vfio_group || !cl->device) {
		fprintf(stderr, "I need a group and a device\n");
		goto err;
	}
#endif

	print_opts(cl);
	return;

err:
	usage(argv[0], cl);
	exit(1);
}
