#include <linux/linkage.h>
#include <arch/asm-common.h>
#include <arch/asm-debug.h>

/**
 * uc64_debug_puts - print a string
 * r0: the address of the string
 * r1: the length of the string
 *
 * The pseudo-logic of this function is:
 *	if (r1 > maxlen)	print error infomation;
 *	while (*r0 && r1-- > 0) {
 *		__putchar(*r0);
 *		r0++;
 *	}
 */
ENTRY(uc64_debug_puts)
	dcmpsub.a	r1, #UC64_DEBUG_PUTS_MAXLEN
	beb		1001f

	adr		r0, 1003f

1001:	dsub.a		r1, r1, #1
	bsl		1002f

	ldb.w		r2, [r0]+, #1
	dcmpsub.a	r2, #0
	beq		1002f

	__putchar	r2

	b		1001b

1002:	return

1003:	.asciz	"\nWarning: String is too long in uc64_debug_puts.\n"
ENDPROC(uc64_debug_puts)

/**
 * uc64_debug_putx - print a data in hex format
 * r0: the data to be printed
 */
ENTRY(uc64_debug_putx)
	__putdata	r0

	/* ____debug_putx: we add a blank after data */
	mov		r0, #0x20
	__putchar	r0

	return
ENDPROC(uc64_debug_putx)
