#ifndef __UNICORE64_ASM_SIGCONTEXT_H__
#define __UNICORE64_ASM_SIGCONTEXT_H__

#include <asm/ptrace.h>
/*
 * Signal context structure - contains all info to do with the state
 * before the signal handler was invoked.  Note: only add new entries
 * to the end of the structure.
 */
struct sigcontext {
	struct pt_regs regs;
};

#endif /* __UNICORE64_ASM_SIGCONTEXT_H__ */
