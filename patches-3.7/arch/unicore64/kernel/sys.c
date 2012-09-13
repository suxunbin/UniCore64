#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <asm-generic/syscalls.h>

SYSCALL_DEFINE5(clone, unsigned long, clone_flags, unsigned long, newsp,
		void __user *, parent_tid, void __user *, child_tid,
		struct pt_regs *, regs)
{
	BUG();
}

SYSCALL_DEFINE4(execve, const char __user *, filename,
		const char __user *const __user *, argv,
		const char __user *const __user *, envp,
		struct pt_regs *, regs)
{
	BUG();
}

SYSCALL_DEFINE6(mmap, unsigned long, addr, unsigned long, len,
		unsigned long, prot, unsigned long, flags,
		unsigned long, fd, off_t, offset)
{
	BUG();
}

#undef __SYSCALL
#define __SYSCALL(nr, call) [nr] = (call),

void *sys_call_table[__NR_syscalls] = {
	[0 ... __NR_syscalls-1] = sys_ni_syscall,
#include <asm/unistd.h>
};
