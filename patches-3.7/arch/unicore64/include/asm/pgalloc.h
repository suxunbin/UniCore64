#ifndef __UNICORE64_ASM_PGALLOC_H__
#define __UNICORE64_ASM_PGALLOC_H__

extern pgd_t *pgd_alloc(struct mm_struct *);
extern void pgd_free(struct mm_struct *, pgd_t *);

extern pgtable_t pte_alloc_one(struct mm_struct *, unsigned long);
extern pte_t *pte_alloc_one_kernel(struct mm_struct *, unsigned long);

extern void pte_free(struct mm_struct *, pgtable_t);
extern void pte_free_kernel(struct mm_struct *, pte_t *);

extern void pmd_populate(struct mm_struct *, pmd_t *, pgtable_t);
extern void pmd_populate_kernel(struct mm_struct *, pmd_t *, pte_t *);

extern pmd_t *pmd_alloc_one(struct mm_struct *, unsigned long);
extern void pmd_free(struct mm_struct *, pmd_t *);

extern void pud_populate(struct mm_struct *, pud_t *, pmd_t *);

#define __pmd_free_tlb(tlb, pmdp, addr)				\
	do {							\
		tlb_remove_page((tlb), virt_to_page(pmdp));	\
	} while (0)

#define __pte_free_tlb(tlb, ptep, addr)				\
	do {							\
		pgtable_page_dtor(ptep);			\
		tlb_remove_page((tlb), (ptep));			\
	} while (0)

#endif /* __UNICORE64_ASM_PGALLOC_H__ */
