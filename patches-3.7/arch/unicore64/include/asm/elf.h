#ifndef __UNICORE64_ASM_ELF_H__
#define __UNICORE64_ASM_ELF_H__

#include <linux/ptrace.h>

typedef u64 elf_greg_t;
#define ELF_NGREG (sizeof(struct pt_regs) / sizeof(elf_greg_t))
typedef elf_greg_t elf_gregset_t[ELF_NGREG];

#define EM_UNICORE64		200

#define ELF_CLASS		ELFCLASS64
#define ELF_DATA		ELFDATA2LSB
#define ELF_ARCH		EM_UNICORE64
#define ELF_PLATFORM		"uc64"
#define ELF_EXEC_PAGESIZE	PAGE_SIZE

#define FP_REGS_NUMBER		33

struct fpu_regs {
	unsigned int regs[FP_REGS_NUMBER];
};

typedef struct fpu_regs elf_fpregset_t;

/*
 * This yields a mask that user programs can use to figure out what
 * instruction set this cpu supports.
 */
#define ELF_HWCAP              0

/*
 * This is used to ensure we don't load something for the wrong architecture.
 */
#define elf_check_arch(x)	((x)->e_machine == EM_UNICORE64)

#define SET_PERSONALITY(ex)	set_personality(PER_LINUX)

/*
 * This is the location that an ET_DYN program is loaded if exec'ed.  Typical
 * use of this is to invoke "./ld.so someprog" to test out a new version of
 * the loader.  We need to make sure that it is out of the way of the program
 * that it will "exec", and that there is sufficient room for the brk.
 */

#define ELF_ET_DYN_BASE		(2 * TASK_SIZE / 3)

#endif /* __UNICORE64_ASM_ELF_H__ */
