#ifndef __ASM_UNICORE64_MMU_CONTEXT_H__
#define __ASM_UNICORE64_MMU_CONTEXT_H__

#include <asm-generic/mm_hooks.h>

#define init_new_context(tsk, mm)	(0)

#define destroy_context(mm)		do { } while (0)
#define enter_lazy_tlb(mm, tsk)		do { } while (0)
#define deactivate_mm(tsk, mm)		do { } while (0)
#define activate_mm(prev, next)		switch_mm((prev), (next), NULL)

static inline void switch_mm(struct mm_struct *prev, struct mm_struct *next,
	  struct task_struct *tsk)
{
	BUG();
}

#endif /* __ASM_UNICORE64_MMU_CONTEXT_H__ */
