#if !defined(__UNICORE64_ASM_UNISTD_H__) || defined(__SYSCALL)
#define __UNICORE64_ASM_UNISTD_H__

#define __ARCH_WANT_SYNC_FILE_RANGE2
#define __ARCH_WANT_SYSCALL_NO_AT
#define __ARCH_WANT_SYS_EXECVE

#define sys_mmap		sys_mmap_pgoff

/* Use the standard ABI for syscalls. */
#include <asm-generic/unistd.h>

#endif /* __UNICORE64_ASM_UNISTD_H__ */
