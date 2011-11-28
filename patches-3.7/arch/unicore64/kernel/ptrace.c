#include <linux/kernel.h>
#include <linux/ptrace.h>

/**
 * ptrace_disable() - Called by kernel/ptrace.c when detaching
 * @child:
 */
void ptrace_disable(struct task_struct *child)
{
	BUG();
}

/**
 * arch_ptrace() -
 * @child:
 * @request:
 * @addr:
 * @data:
 */
long arch_ptrace(struct task_struct *child, long request,
		 unsigned long addr, unsigned long data)
{
	BUG();
	return 0;
}
