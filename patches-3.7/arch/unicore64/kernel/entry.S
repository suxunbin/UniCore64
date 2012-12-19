#include <linux/linkage.h>
#include <generated/asm-offsets.h>
#include <asm/thread_info.h>
#include <asm/cache.h>
#include <arch/asm-common.h>
#include <arch/asm-debug.h>
#include <arch/asm-mmuops.h>
#include <arch/hwdef-cp0-sysctrl.h>

	.macro		__thread_info, rd
	dasr		&rd, sp, #13
	dlsl		&rd, &rd, #13
	.endm

	.macro		__context_save
	@ step 1: push special registers into stack, see struct pt_regs
	movc		lr, CP0_TRAPADDR, #1
	__push		lr				@ push r31(pc)
	dmov		lr, #-1
	__push		lr				@ push return value
	movc		lr, CP0_SYSU, #0
	__push		lr				@ push swr #0
	dmov		lr, bsr
	__push		lr				@ push bsr
	dmov		lr, bfr
	__push		lr				@ push bfr

	@ step 2: push general registers into stack, see struct pt_regs
	.irp		n, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16 \
			, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0
	__push		r\n
	.endr
	.endm

	.macro		__context_restore
	@ step 1: pop general registers from stack, see struct pt_regs
	.irp		n, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, \
			15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28
	__pop		r\n				@ pop r0-r28 regs
	.endr

	@ step 2: pop special registers from stack, see struct pt_regs
	__pop		lr				@ pop bfr
	dmov		bfr, lr
	__pop		lr				@ pop bsr
	dmov		bsr, lr
	__pop		lr				@ pop swr #0
	movc		CP0_SYSU, lr, #0
	__pop		lr				@ pop return value
	__pop		lr				@ pop r31(pc)
	movc		CP0_TRAPADDR, lr, #1		@ saved in epc reg
	.endm

/**
 * ret_from_fork - This is how we return from a fork.
 */
ENTRY(ret_from_fork)
	call		schedule_tail
1001:	__irq_disable
	__thread_info	r17
	ldw		r18, [r17+], #THREAD_INFO_FLAGS
	and		r0, r18, #(1 << TIF_NEED_RESCHED)	@ FIXME: wait for and.a
	cmpsub.a	r0, #0
	adr		lr, 1001b
	bne		schedule		@ return to 1001b
	and		r1, r18, #(1 << TIF_NOTIFY_RESUME | 1 << TIF_SIGPENDING)
	cmpsub.a	r1, #0
	dmov		r0, sp			@ 'regs'
	dmov		r2, #0			@ 'syscall'
	bne.l		do_notify_resume
	__thread_info	r17
	ldw		r18, [r17+], #THREAD_INFO_FLAGS
	cmpsub.a	r18, #0
	bne		__vec_invalid		@ print error information
	__context_restore
	ldd.wu		lr, [sp]+, #8
	ldd.wu		sp, [sp]+, #8
	eret
ENDPROC(ret_from_fork)

ENTRY(ret_from_kthread)
	call		schedule_tail
	dmov		r0, r17
	adr		lr, 1001b
	jump		r18
ENDPROC(ret_from_kthread)

ENTRY(__vec_invalid)
	dmovl		r0, 0xdeaddeaddeaddead
	__putdata	r0
	__putdata	lr
	__halt					@ no return for invalid vec
ENDPROC(__vec_invalid)

ENTRY(__vec_jepriv)
	std.wu		sp, [sp-], #8
	std.wu		lr, [sp-], #8
	__context_save

	/*
	 * Get the system call number.
	 */
	movc		r15, CP0_TRAPADDR, #1	@ saved in epc reg
	dsub		r15, r15, #4
	ldw		r15, [r15+], #0

	__irq_enable

	ldd		r17, =sys_call_table	@ load syscall table pointer

	dmovl		r18, #0xffffff		@ mask off SWI op-code
	dand		r15, r15, r18		@ mask off SWI op-code

	dlsl		r15, r15, #3
	ldd		r18, [r17+], r15	@ call sys_* routine
	std.w		r5, [sp-], #8		@ push fifth and sixth args
	std.w		r4, [sp-], #8
	call.r		r18
	dadd		sp, sp, #16
	std.w		r0, [sp+], #0

ret_syscall:
	__irq_disable
	__thread_info	r17
	ldw		r18, [r17+], #THREAD_INFO_FLAGS
	and		r0, r18, #(1 << TIF_NEED_RESCHED)
	cmpsub.a	r0, #0
	adr		lr, ret_syscall
	bne		schedule
	and		r1, r18, #(1 << TIF_NOTIFY_RESUME | 1 << TIF_SIGPENDING)
	cmpsub.a	r1, #0
	dmov		r0, sp			@ 'regs'
	dmov		r2, #0			@ 'syscall'
	bne.l		do_notify_resume
	__thread_info	r17
	ldw		r18, [r17+], #THREAD_INFO_FLAGS
	cmpsub.a	r18, #0
	bne		__vec_invalid		@ print error information
	__context_restore
	ldd.wu		lr, [sp]+, #8
	ldd.wu		sp, [sp]+, #8
	eret
ENDPROC(__vec_jepriv)

ENTRY(__vec_itrap)
	__push		sp				@ push r29(sp)
	__push		lr				@ push r30(lr)
	__context_save

	@
	@ set args, then call itrap main handler
	@
	@ r0 - address of faulting instruction
	@ r1 - pointer to registers on stack
	@
	movc		r0, CP0_TRAPADDR, #1
	dmov		r1, sp

	__irq_enable

	call		__do_itrap

	__irq_disable

	__context_restore
	__pop		lr				@ pop r30(lr)
	__pop		sp				@ pop r29(sp)
	eret
ENDPROC(__vec_itrap)

ENTRY(__vec_dtrap)
	__push		sp				@ push r29(sp)
	__push		lr				@ push r30(lr)
	__context_save

	@
	@ set args, then call dtrap main handler
	@
	@ r0 - address of faulting address
	@ r1 - pointer to registers on stack
	@
	movc		r0, CP0_TRAPADDR, #0
	dmov		r1, sp

	__irq_enable

	call		__do_dtrap

	__irq_disable

	__context_restore
	__pop		lr				@ pop r30(lr)
	__pop		sp				@ pop r29(sp)
	eret
ENDPROC(__vec_dtrap)

ENTRY(__vec_int_puv3)
	__push		sp				@ push r29(sp)
	__push		lr				@ push r30(lr)
	__context_save
#ifdef CONFIG_ARCH_PUV3
	call		puv3_intc_handler
#endif
	__context_restore
	__pop		lr				@ pop r30(lr)
	__pop		sp				@ pop r29(sp)
	eret
ENDPROC(__vec_int_puv3)

ENTRY(__vec_int_itimer)
	movc		CP0_SYSU, r0, #4
	dmov		r0, bsr
	dand		r0, r0, #7
	cmpsub.a	r0, #1
	movc		r0, CP0_SYSU, #4
	beq		user_entry
	__push		sp				@ push r29(sp)
	__push		lr				@ push r30(lr)
	b		start_save
user_entry:
	std.wu		sp, [sp-], #8
	std.wu		lr, [sp-], #8
start_save:
	__context_save

	@ void __itimer_irqhandler(struct pt_regs *regs)
	dmov		r0, sp
	call		__itimer_irqhandler

	ldd		r17, [sp+], #240	@ get bsr
	dand		r17, r17, #7
	cmpsub.a	r17, #1
	beq		ret_syscall

	__context_restore
	__pop		lr				@ pop r30(lr)
	__pop		sp				@ pop r29(sp)
	eret
ENDPROC(__vec_int_itimer)

	.p2align	L1_CACHE_SHIFT
ENTRY(__vectors_table)
	call		__vec_invalid			@ 0x00: RESET
	call		__vec_invalid			@ 0x04: EEXTN
	b		__vec_jepriv			@ 0x08: ESWI
	b		__vec_itrap			@ 0x0c: ITRAP
	b		__vec_dtrap			@ 0x10: DTRAP
	call		__vec_invalid			@ 0x14: FPU_EXC
	call		__vec_invalid			@ 0x18: INT_KERNEL
	call		__vec_invalid			@ 0x1c: INT_FAULT
	b		__vec_int_itimer		@ 0x20: INT_TIMER
	b		__vec_int_puv3			@ 0x24: INT_PE
	call		__vec_invalid			@ 0x28: INT_OST
	call		__vec_invalid			@ 0x2c: INT_PM
ENDPROC(__vectors_table)

ENTRY(sys_clone)
	dadd		ip, sp, #16
	std		ip, [sp+], #8
	b		sys_clone_wrapper
ENDPROC(sys_clone)
