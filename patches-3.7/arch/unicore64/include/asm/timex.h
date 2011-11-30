#ifndef __UNICORE64_ASM_TIMEX_H__
#define __UNICORE64_ASM_TIMEX_H__

#ifdef CONFIG_ARCH_FPGA
/* in FPGA, OST clock is 32K */
#   define CLOCK_TICK_RATE		(32*1024)
#endif /* CONFIG_ARCH_FPGA */

#include <asm-generic/timex.h>

#endif /* __UNICORE64_ASM_TIMEX_H__ */
