#ifndef __UNICORE64_ASM_PGTABLE_H__
#define __UNICORE64_ASM_PGTABLE_H__

#include <asm/pgtable-prot.h>
#include <asm/pgtable-swap.h>

#include <arch/hwdef-pgtable.h>
#include <arch/hwdef-memory.h>

#include <asm-generic/pgtable-nopud.h>

#define VMALLOC_START		UC64_VM_VMALLOC_START
#define VMALLOC_END		UC64_VM_VMALLOC_END

#define FIRST_USER_ADDRESS	UC64_VM_USER_START

#define PGDIR_SHIFT		UC64_PGD_SHIFT
#define PGDIR_SIZE		UC64_PGD_SIZE
#define PGDIR_MASK		__BM(PGDIR_SHIFT, 0)

#define PMD_SHIFT		UC64_PMD_SHIFT
#define PMD_SIZE		UC64_PMD_SIZE
#define PMD_MASK		__BM(PMD_SHIFT, 0)

#define PTRS_PER_PGD		__BP(UC64_PGD_BITS)
#define PTRS_PER_PMD		__BP(UC64_PMD_BITS)
#define PTRS_PER_PTE		__BP(UC64_PTE_BITS)

extern pgd_t swapper_pg_dir[PTRS_PER_PGD];

#define pgd_index(addr)		(((addr) >> PGDIR_SHIFT) & (PTRS_PER_PGD - 1))
#define pmd_index(addr)		(((addr) >> PMD_SHIFT) & (PTRS_PER_PMD - 1))
#define pte_index(addr)		(((addr) >> PAGE_SHIFT) & (PTRS_PER_PTE - 1))

#define pgd_offset(mm, addr)	((mm)->pgd + pgd_index(addr))
#define pgd_offset_k(addr)	pgd_offset(&init_mm, addr)

#define pmd_offset(pudp, addr)			\
	__va((pmd_t *)(pud_val(*(pudp)) & PAGE_MASK) + pmd_index(addr))

#define pte_offset_kernel(pmdp, addr)		\
	__va((pte_t *)(pmd_val(*(pmdp)) & PAGE_MASK) + pte_index(addr))

#define pte_offset_map(dir, addr)	pte_offset_kernel((dir), (addr))
#define pte_unmap(pte)			do { } while (0)
#define pte_modify(pte, newprot)	__pte((pte_val(pte) & ~UC64_PTE_RWX) \
					| (pgprot_val(newprot) & UC64_PTE_RWX))

/* ZERO_PAGE is a global shared page that is always zero,
 * used for zero-mapped memory areas etc..  */
extern struct page *empty_zero_page;
#define ZERO_PAGE(vaddr)	(empty_zero_page)

#define pte_pfn(pte)		(pte_val(pte) >> PAGE_SHIFT)
#define pfn_pte(pfn, prot)	__pte(((pfn) << PAGE_SHIFT) | pgprot_val(prot))
#define mk_pte(page, prot)	pfn_pte(page_to_pfn(page), prot)

#define pud_none(pud)		(!pud_val(pud))
#define pmd_none(pmd)		(!pmd_val(pmd))
#define pte_none(pte)		(!pte_val(pte))
#define pud_bad(pud)		(!pud_val(pud))
#define pmd_bad(pmd)		(!pmd_val(pmd))
#define pud_present(pud)	(pud_val(pud))
#define pmd_present(pmd)	(pmd_val(pmd) & UC64_PMD_EXIST)
#define pte_present(pte)	(pte_val(pte) & UC64_PTE_EXIST)

extern void set_pte(pte_t *ptep, pte_t pteval);
#define set_pte_at(mm, addr, ptep, pteval)	set_pte(ptep, pteval)
#define set_pmd(pmdptr, pmdval)		do { *(pmdptr) = pmdval; } while (0)
#define set_pud(pudptr, pudval)		do { *(pudptr) = pudval; } while (0)

#define pud_clear(pudp)			set_pud(pudp, __pud(0))
#define pmd_clear(pmdp)			set_pmd(pmdp, __pmd(0))
#define pte_clear(mm, addr, ptep)	set_pte(ptep, __pte(0))

#define pmd_page(pmd)		pfn_to_page((pmd_val(pmd)) >> PAGE_SHIFT)
#define pte_page(pte)		pfn_to_page(pte_pfn(pte))
#define pmd_pgtable(pmd)	pmd_page(pmd)

#define pte_write(pte)		(pte_val(pte) & UC64_PTE_WRITE)
#define pte_dirty(pte)		(pte_val(pte) & UC64_PTE_DIRTY)
#define pte_young(pte)		(pte_val(pte) & UC64_PTE_YOUNG)
#define pte_special(pte)	(0)

#define pte_wrprotect(pte)	(__pte(pte_val(pte) & ~UC64_PTE_WRITE))
#define pte_mkwrite(pte)	(__pte(pte_val(pte) | UC64_PTE_WRITE))
#define pte_mkclean(pte)	(__pte(pte_val(pte) & ~UC64_PTE_DIRTY))
#define pte_mkdirty(pte)	(__pte(pte_val(pte) | UC64_PTE_DIRTY))
#define pte_mkold(pte)		(__pte(pte_val(pte) & ~UC64_PTE_YOUNG))
#define pte_mkyoung(pte)	(__pte(pte_val(pte) | UC64_PTE_YOUNG))
#define pte_mkspecial(pte)	(pte)

#define pgtable_cache_init()		do { } while (0)
#define check_pgt_cache()		do { } while (0)

#define pgd_ERROR(pgd)			pr_err("%s:%d: bad pgd %016lx.\n", \
					__FILE__, __LINE__, pgd_val(pgd))
#define pmd_ERROR(pmd)			pr_err("%s:%d: bad pmd %016lx.\n", \
					__FILE__, __LINE__, pmd_val(pmd))

#include <asm-generic/pgtable.h>

/*
 * Remap a physical page `pfn' of size `size' with page protection `prot'
 * into virtual address `from'
 */
#define io_remap_pfn_range(vma, from, pfn, size, prot) \
		remap_pfn_range(vma, from, pfn, size, prot)

#endif /* __UNICORE64_ASM_PGTABLE_H__ */
