#ifndef __UNICORE64_ASM_CMPXCHG_H__
#define __UNICORE64_ASM_CMPXCHG_H__

#include <asm/barrier.h>

#include <arch/asm-debug.h>

/* This function doesn't exist, so you'll get a linker error
   if something tries to do an invalid cmpxchg().  */
extern void __cmpxchg_called_with_bad_pointer(void);

static inline unsigned long __cmpxchg(volatile void *ptr, unsigned long old,
				unsigned long new, int size)
{
	unsigned long res = 0;

	smp_mb();

	switch (size) {
	case 4:
		__asm__ __volatile__(
			"1:	llw		%0, [%1]\n"
			"	cmpsub.a	%0, %2\n"
			"	bne		2f\n"
			"	mov		%0, %3\n"
			"	scw		%0, [%1]\n"
			"	cmpsub.a	%0, #0\n"
			"	beq		1b\n"
			"	mov		%0, %2\n"
			"2:"
			: "=&r" (res)
			: "r" (ptr), "r" (old), "r" (new)
			: "cc", "memory");
		break;
	case 8:
		__asm__ __volatile__(
			"1:	lld		%0, [%1]\n"
			"	dcmpsub.a	%0, %2\n"
			"	bne		2f\n"
			"	dmov		%0, %3\n"
			"	scd		%0, [%1]\n"
			"	dcmpsub.a	%0, #0\n"
			"	beq		1b\n"
			"	dmov		%0, %2\n"
			"2:"
			: "=&r" (res)
			: "r" (ptr), "r" (old), "r" (new)
			: "cc", "memory");
		break;
	default:
		__cmpxchg_called_with_bad_pointer();
	}

	smp_mb();

	return res;
}

#define cmpxchg(ptr, o, n)						\
	((__typeof__(*(ptr)))__cmpxchg((ptr),				\
					  (unsigned long)(o),		\
					  (unsigned long)(n),		\
					  sizeof(*(ptr))))

extern void __xchg_called_with_bad_pointer(void);

static inline unsigned long __xchg(unsigned long x, volatile void *ptr,
				int size)
{
	unsigned long ret;

	switch (size) {
	case 4:
		__asm__ __volatile__(
			"swapw	%0, [%1], %2"
			: "=&r" (ret)
			: "r" (ptr), "r" (x)
			: "cc", "memory");
		break;
	case 8:
		__asm__ __volatile__(
			"swapd	%0, [%1], %2"
			: "=&r" (ret)
			: "r" (ptr), "r" (x)
			: "cc", "memory");
		break;
	default:
		__xchg_called_with_bad_pointer();
	}

	return ret;
}

#define xchg(ptr, x) \
	((__typeof__(*(ptr)))__xchg((unsigned long)(x), (ptr), sizeof(*(ptr))))

#endif /* __UNICORE64_ASM_CMPXCHG_H__ */
