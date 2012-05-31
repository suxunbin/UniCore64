#ifndef __UNICORE64_ARCH_ASM_DEBUG_H__
#define __UNICORE64_ARCH_ASM_DEBUG_H__

#include <arch/asm-common.h>

/**
 * __putchar - prints a 8 bits char
 * __putdata - prints a 64 bits data
 */
#ifdef	CONFIG_DEBUG_OCD
/* For OCD debug mode */
__ASMMACRO_WRAP(.macro	__putchar, rchar;
			movc	p0.c12, &rchar, #7;
			dmov	&rchar, #1;
			movc	p0.c12, &rchar, #6;
			bkpt;
			movc	&rchar, p0.c12, #7;
		.endm)

__ASMMACRO_WRAP(.macro	__putdata, rdata;
			movc	p0.c12, &rdata, #7;
			dmov	&rdata, #0;
			movc	p0.c12, &rdata, #6;
			bkpt;
			movc	&rdata, p0.c12, #7;
		.endm)
#endif /* CONFIG_DEBUG_OCD */

#define UC64_DEBUG_PUTS_MAXLEN		256

#ifndef __ASSEMBLY__
extern void uc64_debug_puts(const char *s, unsigned len);
extern void uc64_debug_putx(unsigned long x);
#endif /* __ASSEMBLY__ */

#endif /* __UNICORE64_ARCH_ASM_DEBUG_H__ */
