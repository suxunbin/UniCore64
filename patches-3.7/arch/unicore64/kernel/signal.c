#include <linux/syscalls.h>

SYSCALL_DEFINE3(sigaltstack, const stack_t __user *, uss,
		stack_t __user *, uoss,	struct pt_regs *, regs)
{
	BUG();
}

SYSCALL_DEFINE1(rt_sigreturn, struct pt_regs *, regs)
{
	BUG();
}

