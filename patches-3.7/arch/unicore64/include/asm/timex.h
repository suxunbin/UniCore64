#ifndef __UNICORE64_ASM_TIMEX_H__
#define __UNICORE64_ASM_TIMEX_H__

#include <asm/sizes.h>

#ifdef CONFIG_ARCH_FPGA
/*
 * In FPGA, itimer clock is 5M. It takes too much time to handle regular timer
 * interrupts in a second. Set CLOCK_TICK_RATE at X*5M to have 10 interrupts
 * a second instead.
 */
#	define CLOCK_TICK_RATE		((CONFIG_HZ / 10) * (5 * SZ_1M))
#endif /* CONFIG_ARCH_FPGA */

#include <asm-generic/timex.h>

#endif /* __UNICORE64_ASM_TIMEX_H__ */
