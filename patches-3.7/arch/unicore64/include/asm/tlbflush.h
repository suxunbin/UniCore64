#ifndef __UNICORE64_ASM_TLBFLUSH_H__
#define __UNICORE64_ASM_TLBFLUSH_H__

#include <linux/mm.h>
#include <linux/kernel.h>
#include <arch/asm-mmuops.h>

/* following macros used for asm-generic/tlb.h */
#define tlb_start_vma(tlb, vma)				do { } while (0)
#define tlb_end_vma(tlb, vma)				do { } while (0)
#define __tlb_remove_tlb_entry(tlb, ptep, address)	do { } while (0)

#ifndef CONFIG_SMP

static inline void flush_tlb_mm(struct mm_struct *mm)
{
	__invalid_tlb();
}

static inline void flush_tlb_page(struct vm_area_struct *vma, unsigned long va)
{
	__asm__ __volatile__(
			"__invalid_itlb_by_va	%0\n"
			"__invalid_dtlb_by_va	%0\n"
			: : "r" (va)
			: "memory", "cc");
}

static inline void flush_tlb_range(struct vm_area_struct *vma,
		     unsigned long start, unsigned long end)
{
	__invalid_tlb();
}

#else /* CONFIG_SMP */
extern void flush_tlb_mm(struct mm_struct *);
extern void flush_tlb_page(struct vm_area_struct *, unsigned long);
extern void flush_tlb_range(struct vm_area_struct *, unsigned long,
		unsigned long);
#endif /* CONFIG_SMP */

static inline void flush_tlb_kernel_range(unsigned long start,
		unsigned long end)
{
	/* FIXME */
	BUG();
}

extern void update_mmu_cache(struct vm_area_struct *, unsigned long, pte_t *);

#define tlb_flush(tlb)		flush_tlb_mm((tlb)->mm)

#endif /* __UNICORE64_ASM_TLBFLUSH_H__ */
