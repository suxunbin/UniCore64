#include <linux/kernel.h>
#include <linux/elfcore.h>
#include <linux/bug.h>
#include <linux/sched.h>

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

/**
 * show_stack() -
 * @tsk:
 * @sp:
 */
void show_stack(struct task_struct *tsk, unsigned long *sp)
{
	/* FIXME */
	BUG();
}
