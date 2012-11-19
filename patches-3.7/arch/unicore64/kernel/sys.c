#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <asm-generic/syscalls.h>

SYSCALL_DEFINE6(clone_wrapper, unsigned long, clone_flags, unsigned long, newsp,
		void __user *, parent_tid, int, tls_val,
		void __user *, child_tid, struct pt_regs *, regs)
{
	if (!newsp)
		newsp = regs->UC64_R29;

	return do_fork(clone_flags, newsp, regs, 0,
			parent_tid, child_tid);
}

#undef __SYSCALL
#define __SYSCALL(nr, call) [nr] = (call),

void *sys_call_table[__NR_syscalls] = {
	[0 ... __NR_syscalls-1] = sys_ni_syscall,
#include <asm/unistd.h>
};
