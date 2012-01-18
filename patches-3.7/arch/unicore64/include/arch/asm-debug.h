#ifndef __UNICORE64_ARCH_ASM_DEBUG_H__
#define __UNICORE64_ARCH_ASM_DEBUG_H__

#include <arch/asm-common.h>

/**
 * __putchar - prints a 8 bits char
 * __putdata - prints a 64 bits data
 */
#ifdef	CONFIG_DEBUG_OCD
/* For OCD debug mode */
__ASMMACRO_WRAP(.macro	__putchar, rchar, rt1, rt2;
			mov	&rt1, r0;
			mov	&rt2, r1;
			mov	r0, #1;
			mov	r1, &rchar;
			bkpt;
			mov	r0, &rt1;
			mov	r1, &rt2;
		.endm)

__ASMMACRO_WRAP(.macro	__putdata, rdata, rt1, rt2;
			mov	&rt1, r0;
			mov	&rt2, r1;
			mov	r0, #0;
			mov	r1, &rdata;
			bkpt;
			mov	r0, &rt1;
			mov	r1, &rt2;
		.endm)
#else
/* For RTL simulation environment */
__ASMMACRO_WRAP(.macro	__putchar, rchar, rt1, rt2;
			movc	p6.c0, &rchar, #1;
		.endm)
#endif /* CONFIG_DEBUG_OCD */

#ifndef __ASSEMBLY__
extern void uc64_debug_puts(const char *s);
extern void uc64_debug_putx(unsigned long x);
#endif /* __ASSEMBLY__ */

#endif /* __UNICORE64_ARCH_ASM_DEBUG_H__ */
