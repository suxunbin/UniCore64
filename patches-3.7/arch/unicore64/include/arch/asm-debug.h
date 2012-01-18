#ifndef __UNICORE64_ARCH_ASM_DEBUG_H__
#define __UNICORE64_ARCH_ASM_DEBUG_H__

#include <arch/asm-common.h>

/**
 * uc64_debug_putchar - prints a 8 bits char
 * uc64_debug_putdata - prints a 64 bits data
 */
#ifdef	CONFIG_DEBUG_OCD
/* For OCD debug mode */
__ASMMACRO_WRAP(.macro	uc64_debug_putchar, rchar, rt1, rt2;
			mov	&rt1, r0;
			mov	&rt2, r1;
			mov	r0, #1;
			mov	r1, &rchar;
			bkpt;
			mov	r0, &rt1;
			mov	r1, &rt2;
		.endm)

__ASMMACRO_WRAP(.macro	uc64_debug_putdata, rdata, rt1, rt2;
			mov	&rt1, r0;
			mov	&rt2, r1;
			mov	r0, #0;
			mov	r1, &rdata;
			bkpt;
			mov	r0, #1;
			mov	r1, #0x20;
			bkpt;
			mov	r0, &rt1;
			mov	r1, &rt2;
		.endm)
#else
/* For RTL simulation environment */
__ASMMACRO_WRAP(.macro	uc64_debug_putchar, rchar, rt1, rt2;
			movc	p6.c0, &rchar, #1;
		.endm)
#endif /* CONFIG_DEBUG_OCD */

#ifndef __ASSEMBLY__
extern void uc64_debug_puts(const char *s);
#endif /* __ASSEMBLY__ */

#endif /* __UNICORE64_ARCH_ASM_DEBUG_H__ */
