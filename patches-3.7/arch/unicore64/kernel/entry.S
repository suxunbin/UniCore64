#include <linux/linkage.h>
#include <arch/asm-common.h>

	.macro	__priv_context_save
	/* save all gp registers */
	.irp	n, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, \
		16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 30
	uc64_push	r\n
	.endr

	/* save bsr and bfr */
	mov	bsr, r0
	uc64_push	r0
	mov	bfr, r0
	uc64_push	r0
	.endm

	.macro __priv_context_restore
	/* restore bfr and bsr registers */
	uc64_pop	r0
	mov	bfr, r0
	uc64_pop	r0
	mov	bsr, r0

	/* restore all registers */
	.irp	n, 30, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, \
		15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0
	uc64_pop	r\n
	.endr
	.endm

/**
 * __switch_to - Register switch for UniCore3 processors
 */
ENTRY(__switch_to)
	/* FIXME: */
ENDPROC(__switch_to)

ENTRY(__vectors_table)
	bkpt	0x00	/* 0x00: RESET */
	bkpt	0x04	/* 0x04: EEXTN */
	bkpt	0x08	/* 0x08: ESWI */
	bkpt	0x0c	/* 0x0c: ITRAP */
	bkpt	0x10	/* 0x10: DTRAP */
	bkpt	0x14	/* 0x14: FPU_EXC */
	bkpt	0x18	/* 0x18: INT_KERNEL */
	bkpt	0x1c	/* 0x1c: INT_FAULT */
	bkpt	0x20	/* 0x20: INT_TIMER */
	bkpt	0x24	/* 0x24: INT_PE */
	b	__vec_int_ost	/* 0x28: INT_OST */
	bkpt	0x2c	/* 0x2c: INT_PM */
ENDPROC(__vectors_table)

ENTRY(__vec_int_ost)
	__priv_context_save

	call	uc64_inner_timer_irqhandler

	__priv_context_restore
	eret
ENDPROC(__vec_int_ost)
