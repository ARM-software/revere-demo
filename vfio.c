/* SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright (C) 2018-2019 Arm Ltd.
 * Author: Vincent Stehlé <vincent.stehle@arm.com>
 *
 * This is inspired from Linux Documentation/vfio.txt
 */

#include "vfio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/vfio.h>
#include <assert.h>
#include <stdint.h>
#include <unistd.h>

void vfio_setup(struct vfio *v, const char *vfio_group_filename,
		const char *device_name)
{
	int s;
	struct vfio_group_status group_status = {
		.argsz = sizeof(group_status),
	};
	struct vfio_iommu_type1_info iommu_info = {
		.argsz = sizeof(iommu_info),
	};
	struct vfio_device_info device_info = {
		.argsz = sizeof(device_info),
	};

	assert(v);
	assert(vfio_group_filename);
	assert(device_name);

	memset(v, 0, sizeof(*v));

	/* Create a new container */
	v->container_fd = open("/dev/vfio/vfio", O_RDWR);
	if (v->container_fd == -1)
		err(1, "open /dev/vfio/vfio");

	if (ioctl(v->container_fd, VFIO_GET_API_VERSION) != VFIO_API_VERSION)
		err(1, "Unknown API version");

	if (!ioctl(v->container_fd, VFIO_CHECK_EXTENSION, VFIO_TYPE1_IOMMU))
		err(1, "Doesn't support the IOMMU driver we want");

	/* Open the group */
	v->group_fd = open(vfio_group_filename, O_RDWR);
	if (v->group_fd == -1)
		err(1, "open %s", vfio_group_filename);

	/* Test the group is viable and available */
	s = ioctl(v->group_fd, VFIO_GROUP_GET_STATUS, &group_status);
	if (s)
		err(1, "get group status: %d", s);

	if (!(group_status.flags & VFIO_GROUP_FLAGS_VIABLE))
		errx(1, "Group is not viable");

	/* Add the group to the container */
	s = ioctl(v->group_fd, VFIO_GROUP_SET_CONTAINER, &v->container_fd);
	if (s)
		err(1, "set container: %d", s);

	/* Enable the IOMMU model we want */
	s = ioctl(v->container_fd, VFIO_SET_IOMMU, VFIO_TYPE1_IOMMU);
	if (s)
		err(1, "set iommu: %d", s);

	/* Get addition IOMMU info */
	s = ioctl(v->container_fd, VFIO_IOMMU_GET_INFO, &iommu_info);
	if (s)
		err(1, "get iommu info: %d", s);

	if (iommu_info.flags & VFIO_IOMMU_INFO_PGSIZES)
		printf("Supported page sizes bitmap: %#llx\n",
				iommu_info.iova_pgsizes);

	/* Get a file descriptor for the device */
	v->device_fd = ioctl(v->group_fd, VFIO_GROUP_GET_DEVICE_FD,
				device_name);
	if (v->device_fd <= 0)
		err(1, "get device fd: %d", v->device_fd);

	/* Test and setup the device */
	s = ioctl(v->device_fd, VFIO_DEVICE_GET_INFO, &device_info);
	if (s)
		err(1, "get device info: %d", s);

	printf("num_regions: %d, num_irqs: %d\n", device_info.num_regions,
		device_info.num_irqs);

	if (!(device_info.flags & VFIO_DEVICE_FLAGS_PCI))
		errx(1, "not a pci device");

	// Reset device if supported
	if (device_info.flags & VFIO_DEVICE_FLAGS_RESET) {
		s = ioctl(v->device_fd, VFIO_DEVICE_RESET);
		if (s)
			err(1, "reset device: %d", s);
	}

	// Config region
	v->config_region = (struct vfio_region_info){
		.argsz = sizeof(v->bar0_region),
		.index = VFIO_PCI_CONFIG_REGION_INDEX,
	};

	s = ioctl(v->device_fd, VFIO_DEVICE_GET_REGION_INFO, &v->config_region);
	if (s)
		err(1, "get config region info: %d", s);

	if (!(v->config_region.flags & VFIO_REGION_INFO_FLAG_READ))
		errx(1, "config region not readable");

	if (!(v->config_region.flags & VFIO_REGION_INFO_FLAG_WRITE))
		errx(1, "config region not writable");

	printf("Config size: %lld, offset: %#llx\n", v->config_region.size,
		v->config_region.offset);
}

// Setup a DMA mapping
void vfio_map_dma(struct vfio *v, void *bufs, size_t size, uint64_t iova)
{
	int s;

	assert(v);
	assert(bufs);
	assert(size);

	v->dma_map = (struct vfio_iommu_type1_dma_map){
		.argsz = sizeof(v->dma_map),
		.flags = VFIO_DMA_MAP_FLAG_READ | VFIO_DMA_MAP_FLAG_WRITE,
		.iova = iova, /* Starting address from device view */
		.size = size,
		.vaddr = (__u64)bufs,
	};

	s = ioctl(v->container_fd, VFIO_IOMMU_MAP_DMA, &v->dma_map);
	if (s)
		err(1, "map dma: %d", s);

	printf("Buffers @%p, size: %ld, iova: %#lx\n", bufs, size, iova);
}

void *vfio_map_bar0(struct vfio *v)
{
	int s;

	assert(v);

	v->bar0_region = (struct vfio_region_info){
		.argsz = sizeof(v->bar0_region),
		.index = VFIO_PCI_BAR0_REGION_INDEX,
	};

	s = ioctl(v->device_fd, VFIO_DEVICE_GET_REGION_INFO, &v->bar0_region);
	if (s)
		err(1, "get bar0 region info: %d", s);

	if (!(v->bar0_region.flags & VFIO_REGION_INFO_FLAG_READ))
		errx(1, "bar0 region not readable");

	if (!(v->bar0_region.flags & VFIO_REGION_INFO_FLAG_WRITE))
		errx(1, "bar0 region not writable");

	if (!(v->bar0_region.flags & VFIO_REGION_INFO_FLAG_MMAP))
		errx(1, "bar0 region not mmap'able");

	v->bar0 = mmap(0, v->bar0_region.size, PROT_READ | PROT_WRITE,
			MAP_SHARED, v->device_fd, v->bar0_region.offset);
	if (!v->bar0)
		err(1, "mmap bar0 failed");

	printf("BAR0 @%p, size: %lld, offset: %#llx\n", v->bar0,
		v->bar0_region.size, v->bar0_region.offset);
	return v->bar0;
}

uint8_t vfio_read_config(struct vfio *v, unsigned int off)
{
	ssize_t s;
	uint8_t r;
	off_t o;

	assert(v);

	o = v->config_region.offset + off;
	s = pread(v->device_fd, &r, 1, o);
	if (s != 1)
		err(1, "config read: %ld", s);

	return r;
}

void vfio_write_config(struct vfio *v, unsigned int off, uint8_t val)
{
	ssize_t s;
	off_t o;

	assert(v);

	o = v->config_region.offset + off;
	s = pwrite(v->device_fd, &val, 1, o);
	if (s != 1)
		err(1, "config write: %ld", s);
}

void vfio_teardown(struct vfio *v)
{
	int s;
	struct vfio_iommu_type1_dma_unmap dma_unmap = {
		.argsz = sizeof(dma_unmap),
		.flags = 0,
		.iova  = v->dma_map.iova,
		.size  = v->dma_map.size,
	};

	assert(v);

	if (v->bar0) {
		s = munmap(v->bar0, v->bar0_region.size);
		if (s)
			warn("munmap bar0: %d", s);
	}

	if (v->dma_map.size) {
		s = ioctl(v->container_fd, VFIO_IOMMU_UNMAP_DMA, &dma_unmap);
		if (s)
			warn("unmap dma: %d", s);
	}

	s = close(v->device_fd);
	if (s)
		warn("close device: %d", s);

	s = ioctl(v->group_fd, VFIO_GROUP_UNSET_CONTAINER);
	if (s)
		warn("unset container: %d", s);

	s = close(v->group_fd);
	if (s)
		warn("close group: %d", s);

	s = close(v->container_fd);
	if (s)
		warn("close container: %d", s);

	memset(v, 0, sizeof(*v));
}
