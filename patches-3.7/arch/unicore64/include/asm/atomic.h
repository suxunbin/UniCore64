#ifndef __UNICORE64_ASM_ATOMIC_H__
#define __UNICORE64_ASM_ATOMIC_H__

#include <arch/asm-debug.h>

#ifdef CONFIG_SMP
#ifndef atomic_add_return
#define atomic_add_return(i, v)		\
	({					\
		(v)->counter += i;		\
		uc64_debug_putx(0xdead0011);	\
		0;				\
	})
#endif

#ifndef atomic_sub_return
#define atomic_sub_return(i, v)		\
	({					\
		(v)->counter -= i;		\
		uc64_debug_putx(0xdead0012);	\
		0;				\
	})
#endif

#ifndef atomic_clear_mask
#define atomic_clear_mask(i, v)		\
	({					\
		uc64_debug_putx(0xdead0013);	\
		0;				\
	})
#endif

#ifndef atomic_set_mask
#define atomic_set_mask(i, v)			\
	({					\
		uc64_debug_putx(0xdead0014);	\
		0;				\
	})
#endif
#endif /* CONFIG_SMP */

#include <asm-generic/atomic64.h>
#include <asm-generic/atomic.h>

#endif /* __UNICORE64_ASM_ATOMIC_H__ */
