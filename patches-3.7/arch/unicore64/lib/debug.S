#include <linux/linkage.h>
#include <arch/asm-common.h>
#include <arch/asm-debug.h>

#define UC64_DEBUG_PUTS_MAX	256

/**
 * uc64_debug_puts - print a string less than 256.
 * r0: the address of the string
 * r1: the max length of the string
 */
ENTRY(uc64_debug_puts)
	dmov	r1, #UC64_DEBUG_PUTS_MAX

1001:	ldb.w	r2, [r0]+, #1
	dcsub.a r2, #0
	beq	1003f

	uc64_debug_putchar	r2

	dsub.a	r1, r1, #1
	bsl	1002f
	b	1001b

1002:	adr	r0, 1004f
	b	uc64_debug_puts

1003:	return

1004:
	.asciz	"\nWarning: String is too long in uc64_debug_puts.\n"
	.align 4
ENDPROC(uc64_debug_puts)
