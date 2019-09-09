/* SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright (C) 2018-2019 Arm Ltd.
 * Author: Vincent Stehlé <vincent.stehle@arm.com>
 */

#ifndef VFIO_H_INCLUDED
#define VFIO_H_INCLUDED

#include <stdlib.h>
#include <stdint.h>
#include <linux/vfio.h>
#include "cmdline.h"

struct vfio {
	int container_fd;
	int group_fd;
	int device_fd;
	struct vfio_iommu_type1_dma_map dma_map;
	struct vfio_region_info bar0_region;
	struct vfio_region_info config_region;
	void *bar0;
};

void vfio_setup(struct vfio *v, const struct cmdline *cl);
void vfio_map_dma(struct vfio *v, void *bufs, size_t size, uint64_t iova);
void *vfio_map_bar0(struct vfio *v);
uint8_t vfio_read_config(struct vfio *v, unsigned int off);
void vfio_write_config(struct vfio *v, unsigned int off, uint8_t val);
void vfio_teardown(struct vfio *v);

#endif // VFIO_H_INCLUDED
