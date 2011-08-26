#ifndef __ASM_UNICORE64_PROCESSOR_H__
#define __ASM_UNICORE64_PROCESSOR_H__

#ifdef __KERNEL__

#define TASK_SIZE		PAGE_OFFSET
#define TASK_UNMAPPED_BASE	(PAGE_OFFSET / 8 * 3) /* FIXME */

#define STACK_TOP		TASK_SIZE
#define STACK_TOP_MAX		TASK_SIZE

/*
 * Default implementation of macro that returns current
 * instruction pointer ("program counter").
 */
#define current_text_addr()	({ __label__ _l; _l: &&_l; })

struct thread_struct {
	u64 pc;
};

#define INIT_THREAD		{ }

#define thread_saved_pc(tsk)	((tsk)->thread.pc)

#define prepare_to_copy(tsk)	do { } while (0)
#define release_thread(tsk)	do { } while (0)

#define cpu_relax()		barrier()

/* Create a new kernel thread */
extern int kernel_thread(int (*fn)(void *), void *arg, unsigned long flags);

#endif /* __KERNEL__ */

#endif /* __ASM_UNICORE64_PROCESSOR_H__ */
