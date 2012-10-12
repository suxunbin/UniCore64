#ifndef __UNICORE64_ASM_THREAD_INFO_H__
#define __UNICORE64_ASM_THREAD_INFO_H__

#ifdef __KERNEL__

#include <asm/types.h>
#include <asm/page.h>

#define THREAD_SIZE_ORDER	(1)
#define THREAD_SIZE		(PAGE_SIZE << THREAD_SIZE_ORDER)


#ifndef __ASSEMBLY__

#include <asm/segment.h>

/*
 * low level task data that entry.S needs immediate access to.
 */
struct thread_info {
	struct task_struct	*task;		/* main task structure */
	struct exec_domain	*exec_domain;	/* execution domain */
	__u32			flags;		/* low level flags */
	__s32			preempt_count;	/* <0 => BUG */
	__u32			cpu;		/* current cpu */
	mm_segment_t		addr_limit;	/* address limit */
	struct restart_block	restart_block;
};

#define INIT_THREAD_INFO(tsk)						\
{									\
	.task		= &tsk,						\
	.exec_domain	= &default_exec_domain,				\
	.flags		= 0,						\
	.preempt_count	= INIT_PREEMPT_COUNT,				\
	.cpu		= 0,						\
	.addr_limit	= KERNEL_DS,					\
	.restart_block	= {						\
		.fn	= do_no_restart_syscall,			\
	},								\
}

#define init_thread_info	(init_thread_union.thread_info)

static inline struct thread_info *current_thread_info(void)
{
	register u64 sp __asm__("sp");
	return (struct thread_info *)(sp & ~(THREAD_SIZE - 1));
}

#endif /* !__ASSEMBLY__ */

/*
 * We use bit 30 of the preempt_count to indicate that kernel
 * preemption is occurring.
 */
#define PREEMPT_ACTIVE		0x40000000

/* thread information flags: */
#define TIF_SIGPENDING		0 /* signal pending */
#define TIF_NEED_RESCHED	1 /* rescheduling necessary */
#define TIF_SYSCALL_TRACE	2 /* syscall trace active */
#define TIF_RESTORE_SIGMASK	3 /* restore signal mask in do_signal */
#define TIF_MEMDIE		4 /* is terminating due to OOM killer */
#define TIF_NOTIFY_RESUME	5 /* callback before returning to user */
#define TIF_POLLING_NRFLAG	6 /* true if poll_idle() is polling
				 TIF_NEED_RESCHED */

#endif /* __KERNEL__ */
#endif /* __UNICORE64_ASM_THREAD_INFO_H__ */
