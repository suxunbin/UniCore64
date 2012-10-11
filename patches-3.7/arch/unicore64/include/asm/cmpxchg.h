#ifndef __UNICORE64_ASM_CMPXCHG_H__
#define __UNICORE64_ASM_CMPXCHG_H__

#ifndef CONFIG_SMP
#include <asm-generic/cmpxchg.h>
#else
#include <arch/asm-debug.h>

#define cmpxchg(ptr, o, n)			\
	({					\
		uc64_debug_putx(0xdead0021);	\
		(*ptr);				\
	})

#define xchg(ptr, x)				\
	({					\
		uc64_debug_putx(0xdead0022);	\
		(*ptr);				\
	})
#endif /* CONFIG_SMP */

#endif /* __UNICORE64_ASM_CMPXCHG_H__ */
