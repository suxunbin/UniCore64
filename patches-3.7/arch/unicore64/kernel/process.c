#include <linux/kernel.h>
#include <linux/elfcore.h>

#include <arch/asm-common.h>

asmlinkage void ret_from_fork(void) __asm__("ret_from_fork");
asmlinkage void ret_from_kthread(void) __asm__("ret_from_kthread");

/**
 * copy_thread() - Copy a thread
 * @clone_flags:
 * @stack_start:
 * @stk_sz:
 * @p:
 * @regs:
 */
int copy_thread(unsigned long clone_flags, unsigned long stack_start,
	    unsigned long stk_sz, struct task_struct *p, struct pt_regs *regs)
{
	struct pt_regs *childregs = task_pt_regs(p);

	/* cpu_context is used for __switch_to */
	memset(&p->thread.cpu_context, 0, sizeof(struct cpu_context_save));
	p->thread.cpu_context.r29 = (unsigned long)childregs;

	if (unlikely(!regs)) {
		p->thread.cpu_context.r30 = (unsigned long)ret_from_kthread;
		p->thread.cpu_context.r18 = stack_start; /* fn for fn(arg) */
		p->thread.cpu_context.r17 = stk_sz; /* arg for fn(arg) */
		memset(childregs, 0, sizeof(struct pt_regs));
	} else {
		p->thread.cpu_context.r30 = (unsigned long)ret_from_fork;

		*childregs = *regs;
		childregs->UC64_R00 = 0;
		childregs->UC64_R29 = stack_start;
	}

	return 0;
}

/*
 * When a process does an "exec", machine state like FPU and debug
 * registers need to be reset.  This is a hook function for that.
 * Currently we don't have any such state to reset, so this is empty.
 */
void flush_thread(void)
{
}

/**
 * exit_thread() - Free current thread data structures etc..
 */
void exit_thread(void)
{
}

/**
 * machine_restart() - Reboot the machine
 * @cmd:
 */
void machine_restart(char *cmd)
{
	/* FIXME */
	BUG();
}

/**
 * machine_halt() - Halt the machine
 */
void machine_halt(void)
{
	__halt();
}

/**
 * machine_power_off() - Power off the machine
 */
void machine_power_off(void)
{
	/* FIXME */
	BUG();
}

/**
 * Function pointers to optional machine specific functions
 */
void (*pm_power_off)(void) = NULL;

/**
 * get_wchan() -
 * @p:
 */
unsigned long get_wchan(struct task_struct *p)
{
	unsigned long fp, sp, lr;
	int count = 0;
	if (!p || p == current || p->state == TASK_RUNNING)
		return 0;

	fp = thread_saved_fp(p);
	sp = thread_saved_sp(p);
	do {
		unsigned long high, low;
		low = sp;
		high = ALIGN(low, THREAD_SIZE);
		if (fp < (low + 24) || (fp + 8) >= high)
			return 0;
		lr = *(unsigned long *)(fp - 8);
		if (!in_sched_functions(lr))
			return lr;
		sp = *(unsigned long *)(fp - 16);
		fp = *(unsigned long *)(fp - 24);
	} while (count++ < 16);
	return 0;
}

/**
 * cpu_idle() - The idle thread
 *
 * The idle thread. There's no useful work to be
 * done, so just try to conserve power and have a
 * low exit latency (ie sit in a loop waiting for
 * somebody to say that they'd like to reschedule)
 */
void cpu_idle(void)
{
	/* endless idle loop with no priority at all */
	while (1) {
		/* FIXME: here we do some critical things */
		schedule_preempt_disabled();
	}
}
