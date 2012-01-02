#ifndef __UNICORE64_ASM_SETUP_ARCH_H__
#define __UNICORE64_ASM_SETUP_ARCH_H__

#include <linux/stringify.h>
#include <arch/hwdef-copro.h>

extern void setup_arch_cpuinfo(void);
extern void setup_arch_memory(void);
extern void setup_arch_devtree(char *cmdline);

#define UC64_CPUID							\
	({								\
		unsigned long __val;					\
		asm("movc	%0, " __stringify(CP0_CPUID) ", #0"	\
		    : "=r" (__val));					\
		__val;							\
	})

#define UC64_CACHETYPE							\
	({								\
		unsigned long __val;					\
		asm("movc	%0, " __stringify(CP0_CPUID) ", #1"	\
		    : "=r" (__val));					\
		__val;							\
	})

#endif /* __UNICORE64_ASM_SETUP_ARCH_H__ */
