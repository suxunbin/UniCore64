#ifndef __UNICORE64_ARCH_ASM_DEBUG_H__
#define __UNICORE64_ARCH_ASM_DEBUG_H__

#include <arch/asm-common.h>

/**
  * uc64_debug_putchar - prints a 8 bits char
  */
#ifdef	CONFIG_DEBUG_OCD
__ASMMACRO_WRAP(.macro	uc64_debug_putchar, rt;
			movc	p6.c0, &rt, #1;
		.endm)
#endif /* CONFIG_DEBUG_OCD */

#ifndef __ASSEMBLY__
extern void uc64_debug_puts(const char *s);
#endif /* __ASSEMBLY__ */

#endif /* __UNICORE64_ARCH_ASM_DEBUG_H__ */
