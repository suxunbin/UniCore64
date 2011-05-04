#ifndef __ASM_UNICORE64_PGTABLE_H__
#define __ASM_UNICORE64_PGTABLE_H__

#include <asm-generic/pgtable-nopud.h>
#include <asm/pgtable-hwdef.h>

/* FIXME */
#define VMALLOC_START		_AC(0x0000000100000000, UL)
#define VMALLOC_END		_AC(0x0000000200000000, UL)

/* 3-level translation table walking: 9+9+9+12 */
#define PGDIR_SHIFT		(30)
#define PMD_SHIFT		(21)

#define PTRS_PER_PMD		(1 << 9)

#define pud_none(pud)		(!pud_val(pud))
#define pud_bad(pud)		(!pud_val(pud))
#define pud_present(pud)	(pud_val(pud))
#define pud_clear(pudp)		set_pud(pudp, __pud(0))

#define pmd_none(pmd)		(!pmd_val(pmd))
#define pmd_bad(pmd)		(!pmd_val(pmd))
#define pmd_present(pmd)	(pmd_val(pmd) & UC64_L2_EXIST)
#define pmd_clear(pmdp)		set_pmd(pmdp, __pmd(0))

#define pmd_offset(pudp, addr)	((pmd_t *)pud_val(*(pudp)) +	\
				(((addr) >> PMD_SHIFT) & (PTRS_PER_PMD - 1)))

#define pte_none(pte)		(!pte_val(pte))
#define pte_present(pte)	(pte_val(pte) & UC64_L3_EXIST)
#define pte_clear(mm, addr, ptep)	set_pte(ptep, __pte(0))

#define pte_write(pte)		(pte_val(pte) & UC64_L3_WRITE)
#define pte_dirty(pte)		(pte_val(pte) & UC64_L3_DIRTY)
#define pte_young(pte)		(pte_val(pte) & UC64_L3_YOUNG)

#define pte_wrprotect(pte)	(__pte(pte_val(pte) & ~UC64_L3_WRITE))
#define pte_mkwrite(pte)	(__pte(pte_val(pte) | UC64_L3_WRITE))
#define pte_mkclean(pte)	(__pte(pte_val(pte) & ~UC64_L3_DIRTY))
#define pte_mkdirty(pte)	(__pte(pte_val(pte) | UC64_L3_DIRTY))
#define pte_mkold(pte)		(__pte(pte_val(pte) & ~UC64_L3_YOUNG))
#define pte_mkyoung(pte)	(__pte(pte_val(pte) | UC64_L3_YOUNG))

extern void set_pte(pte_t *ptep, pte_t pteval);
#define set_pte_at(mm, addr, ptep, pteval)	set_pte(ptep, pteval)

#include <asm-generic/pgtable.h>

#endif /* __ASM_UNICORE64_PGTABLE_H__ */
