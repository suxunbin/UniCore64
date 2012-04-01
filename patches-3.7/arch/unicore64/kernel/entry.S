#include <linux/linkage.h>
#include <asm/cache.h>
#include <arch/asm-common.h>
#include <arch/asm-debug.h>
#include <arch/asm-mmuops.h>
#include <arch/hwdef-cp0-sysctrl.h>

	.macro	__priv_context_save
	@ step 1: save r0 and sp to keep their original values
	movc	CP0_SWR, r0, #4
	movc	CP0_SWR, sp, #5

	@ step 2: push special registers into stack, see struct pt_regs
	dmov	r0, #-1
	__push	r0				@ push return value
	movc	r0, CP0_SWR, #0
	__push	r0				@ push swr #0
	dmov	r0, bfr
	__push	r0				@ push bfr
	dmov	r0, bsr
	__push	r0				@ push bsr
	movc	r0, CP0_EPC, #1
	__push	r0				@ push r31(pc)
	__push	lr				@ push r30(lr)
	movc	r0, CP0_SWR, #5
	__push	r0				@ push r29(sp)

	@ step 3: push general registers into stack, see struct pt_regs
	movc	r0, CP0_SWR, #4			@ restore original r0 value
	.irp	n, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, \
		15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0
	__push	r\n
	.endr

	.endm

	.macro __priv_context_restore
	@ step 1: pop only-kernel-awared registers from stack

	@ step 2: pop general registers from stack, see struct pt_regs
	.irp	n, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, \
		16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28
	__pop	r\n				@ pop r0-r28 regs
	.endr

	@ step 3: pop special registers from stack, see struct pt_regs
	__pop	lr				@ pop r29(sp)
	movc	CP0_SWR, lr, #5			@ saved in temp reg
	__pop	lr				@ pop r30(lr)
	movc	CP0_SWR, lr, #4			@ saved in temp reg
	__pop	lr				@ pop r31(pc)
	movc	CP0_EPC, lr, #1			@ saved in epc reg
	__pop	lr				@ pop bsr
	dmov	bsr, lr
	__pop	lr				@ pop bfr
	dmov	bfr, lr
	__pop	lr				@ pop swr #0
	movc	CP0_SWR, lr, #0

	@ step 4: restore the original values of lr and sp
	movc	lr, CP0_SWR, #4			@ restore r30(lr) value
	movc	sp, CP0_SWR, #5			@ restore r29(sp) value
	.endm

/**
 * ret_from_fork - This is how we return from a fork.
 */
ENTRY(ret_from_fork)
	call	schedule_tail
	/* TODO */
ENDPROC(ret_from_fork)

/**
 * __switch_to - Register switch for UniCore3 processors
 */
ENTRY(__switch_to)
	/* FIXME: */
ENDPROC(__switch_to)

ENTRY(__vec_invalid)
	dmovl		r0, 0xdeaddeaddeaddead
	__putdata	r0
	__putdata	lr
	__halt					@ no return for invalid vec
ENDPROC(__vec_invalid)

ENTRY(__vec_itrap)
	__priv_context_save

	@
	@ set args, then call itrap main handler
	@
	@ r0 - address of faulting instruction
	@ r1 - pointer to registers on stack
	@
	movc	r0, CP0_EPC, #1
	dmov	r1, sp

	enable_irq

	call	__do_itrap

	disable_irq

	__priv_context_restore
	eret
ENDPROC(__vec_itrap)

ENTRY(__vec_dtrap)
	__priv_context_save

	@
	@ set args, then call dtrap main handler
	@
	@ r0 - address of faulting address
	@ r1 - pointer to registers on stack
	@
	movc	r0, CP0_EPC, #0
	dmov	r1, sp

	enable_irq

	call	__do_dtrap

	disable_irq

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
	call	__vec_invalid			@ 0x00: RESET
	call	__vec_invalid			@ 0x04: EEXTN
	call	__vec_invalid			@ 0x08: ESWI
	b	__vec_itrap			@ 0x0c: ITRAP
	b	__vec_dtrap			@ 0x10: DTRAP
	call	__vec_invalid			@ 0x14: FPU_EXC
	call	__vec_invalid			@ 0x18: INT_KERNEL
	call	__vec_invalid			@ 0x1c: INT_FAULT
	b	__vec_int_itimer		@ 0x20: INT_TIMER
	b	__vec_int_puv3			@ 0x24: INT_PE
	call	__vec_invalid			@ 0x28: INT_OST
	call	__vec_invalid			@ 0x2c: INT_PM
ENDPROC(__vectors_table)
