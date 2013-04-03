#ifndef __UNICORE64_ASM_TIMEX_H__
#define __UNICORE64_ASM_TIMEX_H__

#include <asm/sizes.h>

#ifdef CONFIG_ARCH_FPGA
/*
 * In FPGA, itimer clock is 3.75M. It takes too much time to handle regular
 * timer interrupts in a second. Set CLOCK_EVENT_TICK_RATE at X*3.75M to have
 * 10 interrupts a second instead.
 *
 * OST clock rate is 32K. CLOCK_TICK_RATE must be modified in the same way with
 * CLOCK_EVENT_TICK_RATE.
 */
#define CLOCK_EVENT_TICK_RATE		((CONFIG_HZ / 10) * (3840 * SZ_1K))
#define CLOCK_TICK_RATE		((CONFIG_HZ / 10) * (32 * SZ_1K))
#endif /* CONFIG_ARCH_FPGA */

#include <asm-generic/timex.h>

#endif /* __UNICORE64_ASM_TIMEX_H__ */
