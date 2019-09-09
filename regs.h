/* SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright (C) 2018-2019 Arm Ltd.
 * Author: Vincent Stehlé <vincent.stehle@arm.com>
 */

#ifndef REGS_H_INCLUDED
#define REGS_H_INCLUDED

#include <stdint.h>

static inline volatile void *regs_addr(void *regs, unsigned int offset)
{
	return (volatile void *)((uintptr_t)regs + offset);
}

static inline uint64_t regs_readq(void *regs, unsigned int offset)
{
	const volatile uint64_t *addr = regs_addr(regs, offset);
	uint64_t val = *addr;

#ifdef __aarch64__
	asm volatile("dsb ld" : : : "memory");
#endif
#ifdef __x86_64__
	asm volatile("" : : : "memory");
#endif
	return val;
}

static inline void regs_writeq(void *regs, uint64_t value, unsigned int offset)
{
	volatile uint64_t *addr = regs_addr(regs, offset);

#ifdef __aarch64__
	asm volatile("dsb st" : : : "memory");
#endif
#ifdef __x86_64__
	asm volatile("" : : : "memory");
#endif
	*addr = value;
}

#endif /* REGS_H_INCLUDED */
