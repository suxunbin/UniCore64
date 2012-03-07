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
	dcmpsub.a	r2, #0
	beq	1003f

	__putchar	r2

	dsub.a	r1, r1, #1
	bsl	1002f
	b	1001b

1002:	adr	r0, 1004f
	b	uc64_debug_puts

1003:	return

1004:
	.asciz	"\nWarning: String is too long in uc64_debug_puts.\n"
ENDPROC(uc64_debug_puts)

/**
 * uc64_debug_putx - print a data in hex format
 * r0: the data to be printed
 */
ENTRY(uc64_debug_putx)
	__putdata	r0

	/* ____debug_putx: we add a blank after data */
	mov	r0, #0x20
	__putchar	r0

	return
ENDPROC(uc64_debug_putx)
