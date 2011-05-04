#ifndef __ASM_UNICORE64_THREAD_INFO_H__
#define __ASM_UNICORE64_THREAD_INFO_H__

#ifdef __KERNEL__

#define THREAD_SIZE_ORDER	(1)
#define THREAD_SIZE		(PAGE_SIZE << THREAD_SIZE_ORDER)

#include <asm/types.h>
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

#endif /* __KERNEL__ */
#endif /* __ASM_UNICORE64_THREAD_INFO_H__ */
