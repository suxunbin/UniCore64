#ifndef __UNICORE64_ASM_PROCESSOR_H__
#define __UNICORE64_ASM_PROCESSOR_H__

#ifdef __KERNEL__

#define TASK_SIZE		UC64_VM_USER_END
#define TASK_UNMAPPED_BASE	(PAGE_ALIGN(TASK_SIZE / 4))

#define STACK_TOP		TASK_SIZE
#define STACK_TOP_MAX		TASK_SIZE

/*
 * Default implementation of macro that returns current
 * instruction pointer ("program counter").
 */
#define current_text_addr()	({ __label__ _l; _l: &&_l; })

struct cpu_context_save {
	unsigned long r16;
	unsigned long r17;
	unsigned long r18;
	unsigned long r19;
	unsigned long r20;
	unsigned long r21;
	unsigned long r22;
	unsigned long r23;
	unsigned long r24;
	unsigned long r25;
	unsigned long r26;
	unsigned long r27;
	unsigned long r29;	/* kernel stack pointer */
	unsigned long r30;	/* return address */
};

struct thread_struct {
	struct cpu_context_save	cpu_context;
};

#define INIT_THREAD		{ }

#define thread_saved_pc(tsk)	((tsk)->thread.cpu_context.r30)
#define thread_saved_sp(tsk)	((tsk)->thread.cpu_context.r29)
#define thread_saved_fp(tsk)	((tsk)->thread.cpu_context.r27)

#define release_thread(tsk)	do { } while (0)

#define cpu_relax()		barrier()

extern unsigned long get_wchan(struct task_struct *p);

/* Return some info about the user process TASK. */
#define KSTK_PTREGS_GAP		L1_CACHE_BYTES /* Only one word for canary */
#define task_pt_regs(tsk)	((struct pt_regs *)			\
				(task_stack_page(tsk) + THREAD_SIZE	\
				- KSTK_PTREGS_GAP - sizeof(struct pt_regs)))
/* Aliases for pc and sp (used in fs/proc/array.c) */
#define KSTK_EIP(tsk)		(task_pt_regs(tsk)->UC64_R31)
#define KSTK_ESP(tsk)		(task_pt_regs(tsk)->UC64_R29)

#endif /* __KERNEL__ */

#define start_thread(regs, pc, sp)					\
({									\
	unsigned long *stack = (unsigned long *)sp;			\
	memset(regs->uc64_regs, 0, sizeof(regs->uc64_regs));		\
	regs->UC64_ASR = ASR_MODE_USER | ASR_T_BIT;				\
	regs->UC64_R31 = pc;		/* pc */                        \
	regs->UC64_R29 = sp;		/* sp */                        \
	regs->UC64_R02 = stack[2];	/* r2 (envp) */                 \
	regs->UC64_R01 = stack[1];	/* r1 (argv) */                 \
	regs->UC64_R00 = stack[0];	/* r0 (argc) */                 \
})

#endif /* __UNICORE64_ASM_PROCESSOR_H__ */
