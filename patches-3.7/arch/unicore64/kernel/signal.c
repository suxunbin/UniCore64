#include <linux/syscalls.h>
#include <linux/tracehook.h>

SYSCALL_DEFINE3(sigaltstack, const stack_t __user *, uss,
		stack_t __user *, uoss,	struct pt_regs *, regs)
{
	BUG();
}

SYSCALL_DEFINE1(rt_sigreturn, struct pt_regs *, regs)
{
	BUG();
}

asmlinkage void do_notify_resume(struct pt_regs *regs,
		unsigned int thread_flags, int syscall)
{
	if (thread_flags & (1 << TIF_SIGPENDING))
		BUG();

	if (thread_flags & (1 << TIF_NOTIFY_RESUME)) {
		clear_thread_flag(TIF_NOTIFY_RESUME);
		tracehook_notify_resume(regs);
	}
}
