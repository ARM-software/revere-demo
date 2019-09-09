/* SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright (C) 2018-2019 Arm Ltd.
 * Author: Vincent Stehlé <vincent.stehle@arm.com>
 */

#include "revere_hw.h"

static volatile void *revere_reg_addr(void *regs, unsigned int offset)
{
	return (volatile void *)((uintptr_t)regs + offset);
}

uint64_t revere_readq(void *regs, unsigned int offset)
{
	const volatile uint64_t *addr = revere_reg_addr(regs, offset);
	uint64_t val = *addr;
#ifdef __aarch64__
	asm volatile("dsb ld" : : : "memory");
#endif
	return val;
}

void revere_writeq(void *regs, uint64_t value, unsigned int offset)
{
	volatile uint64_t *addr = revere_reg_addr(regs, offset);
#ifdef __aarch64__
	asm volatile("dsb st" : : : "memory");
#endif
	*addr = value;
}
