#ifndef __ASM_UNICORE64_ELF_H__
#define __ASM_UNICORE64_ELF_H__

#include <asm/ptrace.h>

typedef u64 elf_greg_t;
#define ELF_NGREG (sizeof(struct pt_regs) / sizeof(elf_greg_t))
typedef elf_greg_t elf_gregset_t[ELF_NGREG];

#define EM_UNICORE64		110 /* FIXME lator */

#define ELF_CLASS		ELFCLASS64
#define ELF_DATA		ELFDATA2LSB
#define ELF_ARCH		EM_UNICORE64
#define ELF_PLATFORM		(NULL)
#define ELF_EXEC_PAGESIZE	PAGE_SIZE

#endif /* __ASM_UNICORE64_ELF_H__ */
