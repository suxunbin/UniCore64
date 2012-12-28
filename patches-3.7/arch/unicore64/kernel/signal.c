#include <linux/syscalls.h>
#include <linux/tracehook.h>

#include <asm-generic/ucontext.h>
#include <asm/uaccess.h>

SYSCALL_DEFINE3(sigaltstack, const stack_t __user *, uss,
		stack_t __user *, uoss,	struct pt_regs *, regs)
{
	BUG();
}

struct rt_sigframe {
	struct ucontext uc;
	unsigned long retcode;
};

SYSCALL_DEFINE0(rt_sigreturn)
{
	struct rt_sigframe __user *frame;
	sigset_t set;

	struct pt_regs *regs = current_pt_regs();
	frame = (struct rt_sigframe __user *)(regs->UC64_R29);

	if (!access_ok(VERIFY_READ, frame, sizeof(*frame)))
		goto badframe;

	set_current_blocked(&set);

	if (__copy_from_user(regs, &frame->uc.uc_mcontext.regs,
				sizeof(struct pt_regs)))
		goto badframe;

	if (!user_mode(regs))
		goto badframe;

	return 0;

badframe:
	force_sig(SIGSEGV, current);
	return 0;
}

/* grab and setup a signal frame.
 *
 * basically we stack a lot of state info, and arrange for the
 * user-mode program to return to the kernel using either a
 * trampoline which performs the syscall sigreturn, or a provided
 * user-mode trampoline.
 */
static int setup_rt_frame(int sig, struct k_sigaction *ka, siginfo_t *info,
			  sigset_t *set, struct pt_regs *regs)
{
	struct rt_sigframe  *frame;
	int err = 0;
	unsigned long sp = regs->UC64_R29;

	frame = (void __user *)((sp - sizeof(*frame)) & ~7);

	if (!access_ok(VERIFY_WRITE, frame, sizeof(*frame)))
		return -EFAULT;

	/*FIXME:check SA_SIGINFO*/

	/* Clear all the bits of the ucontext we don't use.  */
	err |= __clear_user(&frame->uc, offsetof(struct ucontext, uc_mcontext));

	err |= __copy_to_user(&frame->uc.uc_mcontext.regs, regs,
				sizeof(struct pt_regs));

	/*Save jepriv code in frame->retcode*/
	err |= __put_user(0xf000008b, &(frame->retcode));

	if (err)
		return -EFAULT;

	/* Set up registers for signal handler */
	/*R31 saves what we enter NOW*/
	regs->UC64_R31 = (unsigned long)ka->sa.sa_handler;
	/*R30 saves what we enter LATER*/
	regs->UC64_R30 = (unsigned long)&(frame->retcode);
	regs->UC64_R00 = (unsigned long)sig;           /* arg 1: signo */
	/* actually move the usp to reflect the stacked frame */
	regs->UC64_R29 = (unsigned long)frame;

	return 0;
}

static void
handle_signal(unsigned long sig, siginfo_t *info, struct k_sigaction *ka,
		struct pt_regs *regs, int syscall)
{
	int ret;

	/* Are we from a system call? */
	if (syscall) {
		/* If so, check system call restarting.. */
		if (regs->UC64_R00)
			BUG();
	}

	ret = setup_rt_frame(sig, ka, info, sigmask_to_save(), regs);
	if (ret)
		return;

	/* Update the blocked signals */
	signal_delivered(sig, info, ka, regs, 0);
}

void do_signal(struct pt_regs *regs, int syscall)
{
	struct k_sigaction ka;
	siginfo_t info;
	int signr;

	signr = get_signal_to_deliver(&info, &ka, regs, NULL);
	if (signr > 0) {
		/* Whee! Actually deliver the signal.  */
		handle_signal(signr, &info, &ka, regs, syscall);
		return;
	}

	/* FIXME:check did we come from a system call? */
	BUG();
}

asmlinkage void do_notify_resume(unsigned int thread_flags, int syscall)
{
	struct pt_regs *regs = current_pt_regs();

	if (thread_flags & (1 << TIF_SIGPENDING)) {
		do_signal(regs, syscall);
	}

	if (thread_flags & (1 << TIF_NOTIFY_RESUME)) {
		clear_thread_flag(TIF_NOTIFY_RESUME);
		tracehook_notify_resume(regs);
	}
}
