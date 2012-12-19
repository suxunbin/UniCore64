#ifndef __UNICORE64_ASM_ATOMIC_H__
#define __UNICORE64_ASM_ATOMIC_H__

#include <asm/barrier.h>

#include <arch/asm-debug.h>

#ifdef CONFIG_SMP
#ifndef atomic_add_return
#define atomic_add_return(i, v)					\
	({								\
		unsigned long tmp;					\
		int result;						\
		smp_mb();						\
		__asm__ __volatile__(					\
			"1:	llw		%0, [%2]\n"		\
			"	add		%0, %0, %3\n"		\
			"	mov		%1, %0\n"		\
			"	scw		%1, [%2]\n"		\
			"	cmpsub.a	%1, #0\n"		\
			"	beq		1b"			\
			: "=&r" (result), "=&r" (tmp)			\
			: "r" (&(v)->counter), "r" (i)			\
			: "cc", "memory");				\
		smp_mb();						\
		result;							\
	})
#endif

#ifndef atomic_sub_return
#define atomic_sub_return(i, v)					\
	({								\
		unsigned long tmp;					\
		int result;						\
		smp_mb();						\
		__asm__ __volatile__(					\
			"1:	llw		%0, [%2]\n"		\
			"	sub		%0, %0, %3\n"		\
			"	mov		%1, %0\n"		\
			"	scw		%1, [%2]\n"		\
			"	cmpsub.a	%1, #0\n"		\
			"	beq		1b"			\
			: "=&r" (result), "=&r" (tmp)			\
			: "r" (&(v)->counter), "r" (i)			\
			: "cc", "memory");				\
		smp_mb();						\
		result;							\
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
