#ifndef __UNICORE64_ASM_TLBFLUSH_H__
#define __UNICORE64_ASM_TLBFLUSH_H__

/* following macros used for asm-generic/tlb.h */
#define tlb_start_vma(tlb, vma)				do { } while (0)
#define tlb_end_vma(tlb, vma)				do { } while (0)
#define __tlb_remove_tlb_entry(tlb, ptep, address)	do { } while (0)

extern void flush_tlb_mm(struct mm_struct *);
extern void flush_tlb_page(struct vm_area_struct *, unsigned long);
extern void flush_tlb_range(struct vm_area_struct *, unsigned long,	\
		unsigned long);

extern void flush_tlb_kernel_range(unsigned long, unsigned long);

extern void update_mmu_cache(struct vm_area_struct *, unsigned long, pte_t *);

#define tlb_flush(tlb)		flush_tlb_mm((tlb)->mm)

#endif /* __UNICORE64_ASM_TLBFLUSH_H__ */
