#include <linux/kernel.h>
#include <linux/elfcore.h>

/**
 * kernel_thread() - Create a kernel thread
 * @fn:
 * @arg:
 * @flags:
 */
int kernel_thread(int (*fn)(void *), void * arg, unsigned long flags)
{
	/* FIXME */
	BUG();
	return 0;
}

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
	/* FIXME */
	BUG();
	return 0;
}

/**
 * exit_thread() - Free current thread data structures etc..
 */
void exit_thread(void)
{
	/* FIXME */
	BUG();
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
	/* FIXME */
	BUG();
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
	/* FIXME */
	BUG();
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
	/* FIXME */
	BUG();
}

/**
 * dump_fpu() -
 * @regs:
 * @fp:
 */
int dump_fpu(struct pt_regs *regs, elf_fpregset_t *fp)
{
	/* FIXME: fill in the fpe structure for a core dump... */
	BUG();
	return 0;
}

/**
 * show_regs() -
 * @regs:
 */
void show_regs(struct pt_regs *regs)
{
	/* FIXME */
	BUG();
}
