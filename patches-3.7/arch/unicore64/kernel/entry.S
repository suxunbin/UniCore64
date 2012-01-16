#include <linux/linkage.h>
#include <arch/asm-common.h>

	.macro	__priv_context_save
	/* save all registers */
	push_lr
	.endm

	.macro __priv_context_restore
	/* restore all registers */
	pop_lr
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
