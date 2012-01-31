#include <linux/linkage.h>
#include <asm/cache.h>
#include <arch/asm-common.h>
#include <arch/asm-debug.h>
#include <arch/asm-mmuops.h>

	.macro	__priv_context_save
	/* save all gp registers */
	.irp	n, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, \
		16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 30
	__push	r\n
	.endr

	/* save bsr and bfr */
	mov	bsr, r0
	__push	r0
	mov	bfr, r0
	__push	r0
	.endm

	.macro __priv_context_restore
	/* restore bfr and bsr registers */
	__pop	r0
	mov	bfr, r0
	__pop	r0
	mov	bsr, r0

	/* restore all registers */
	.irp	n, 30, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, \
		15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0
	__pop	r\n
	.endr
	.endm

/**
 * __switch_to - Register switch for UniCore3 processors
 */
ENTRY(__switch_to)
	/* FIXME: */
ENDPROC(__switch_to)

ENTRY(__vec_invalid)
	dmovl		r0,  0xdeaddeaddeaddead
	__putdata	r0, r14, r15
	__putdata	lr, r14, r15
	halt		/* no return */
ENDPROC(__vec_invalid)

ENTRY(__vec_itrap)
	__priv_context_save

	call	__do_itrap

	__priv_context_restore
	eret
ENDPROC(__vec_itrap)

ENTRY(__vec_dtrap)
	__priv_context_save

	call	__do_dtrap

	__priv_context_restore
	eret
ENDPROC(__vec_dtrap)

ENTRY(__vec_int_puv3)
	__priv_context_save

	call	puv3_intc_handler

	__priv_context_restore
	eret
ENDPROC(__vec_int_puv3)

ENTRY(__vec_int_itimer)
	__priv_context_save

	call	__itimer_irqhandler

	__priv_context_restore
	eret
ENDPROC(__vec_int_itimer)

	.p2align	L1_CACHE_SHIFT
ENTRY(__vectors_table)
	call	__vec_invalid		/* 0x00: RESET */
	call	__vec_invalid		/* 0x04: EEXTN */
	call	__vec_invalid		/* 0x08: ESWI */
	b	__vec_itrap		/* 0x0c: ITRAP */
	b	__vec_dtrap		/* 0x10: DTRAP */
	call	__vec_invalid		/* 0x14: FPU_EXC */
	call	__vec_invalid		/* 0x18: INT_KERNEL */
	call	__vec_invalid		/* 0x1c: INT_FAULT */
	b	__vec_int_itimer	/* 0x20: INT_TIMER */
	b	__vec_int_puv3		/* 0x24: INT_PE */
	call	__vec_invalid		/* 0x28: INT_OST */
	call	__vec_invalid		/* 0x2c: INT_PM */
ENDPROC(__vectors_table)
