#ifndef __ASM_UNICORE64_PGTABLE_H__
#define __ASM_UNICORE64_PGTABLE_H__

#include <asm-generic/pgtable-nopud.h>
#include <asm/pgtable-hwdef.h>

/* FIXME */
#define VMALLOC_START		_AC(0x0000000100000000, UL)
#define VMALLOC_END		_AC(0x0000000200000000, UL)

#define FIRST_USER_ADDRESS	(0)

/*
 * 3-level translation table walking: 9+9+9+12
 *  PGTBL_ENTRYSHIFT: the logarithm of the size of pagetable entry space,
 *			which is the same for PGD/PMD/PTE, i.e., 8 bytes.
 */
#define PGTBL_ENTRYSHIFT	(3)

#define PGDIR_SHIFT		(PAGE_SHIFT				\
				+ (PAGE_SHIFT - PGTBL_ENTRYSHIFT)	\
				+ (PAGE_SHIFT - PGTBL_ENTRYSHIFT))
#define PGDIR_SIZE		(_AC(1, UL) << PGDIR_SHIFT)
#define PGDIR_MASK		(~(PGDIR_SIZE-1))

#define PMD_SHIFT		(PAGE_SHIFT + (PAGE_SHIFT - PGTBL_ENTRYSHIFT))
#define PMD_SIZE		(_AC(1, UL) << PMD_SHIFT)
#define PMD_MASK		(~(PMD_SIZE-1))

#define PTRS_PER_PGD		(1 << (PAGE_SHIFT - PGTBL_ENTRYSHIFT))
#define PTRS_PER_PMD		(1 << (PAGE_SHIFT - PGTBL_ENTRYSHIFT))
#define PTRS_PER_PTE		(PAGE_SIZE / sizeof(pte_t))

extern pgd_t swapper_pg_dir[PTRS_PER_PGD];

#define pgd_index(addr)		(((addr) >> PGDIR_SHIFT) & (PTRS_PER_PGD - 1))
#define pgd_offset(mm, addr)	((mm)->pgd + pgd_index(addr))
#define pgd_offset_k(addr)	pgd_offset(&init_mm, addr)

#define pmd_index(addr)		(((addr) >> PMD_SHIFT) & (PTRS_PER_PMD - 1))
#define pmd_offset(pudp, addr)	((pmd_t *)pud_val(*(pudp)) + pmd_index(addr))

#define pte_index(addr)		(((addr) >> PAGE_SHIFT) & (PTRS_PER_PTE - 1))
static inline pte_t *pte_offset_kernel(pmd_t *pmd, unsigned long address)
{
	/* FIXME */
	BUG();
	return 0;
}
#define pte_offset_map(dir, addr)	pte_offset_kernel((dir), (addr))
#define pte_unmap(pte)			do { } while (0)

#define PAGE_KERNEL		__pgprot(UC64_L3_READ | UC64_L3_WRITE	\
					| UC64_L3_EXEC | UC64_L3_DIRTY	\
					| UC64_L3_EXIST | UC64_L3_YOUNG	\
					| UC64_L3_CACHE)

/* FIXME: if READ is needed when WRITE or EXEC, otherwise, modify VM_flags */
#define arch_vm_get_page_prot(vm_flags)	__pgprot(UC64_L3_EXIST | UC64_L3_CACHE)
#define __P000		__pgprot(0)
#define __P001		__pgprot(UC64_L3_READ)
#define __P010		__pgprot(0)
#define __P011		__pgprot(UC64_L3_READ)
#define __P100		__pgprot(UC64_L3_EXEC)
#define __P101		__pgprot(UC64_L3_EXEC | UC64_L3_READ)
#define __P110		__pgprot(UC64_L3_EXEC)
#define __P111		__pgprot(UC64_L3_EXEC | UC64_L3_READ)

#define __S000		__pgprot(0)
#define __S001		__pgprot(UC64_L3_READ)
#define __S010		__pgprot(UC64_L3_WRITE)
#define __S011		__pgprot(UC64_L3_WRITE | UC64_L3_READ)
#define __S100		__pgprot(UC64_L3_EXEC)
#define __S101		__pgprot(UC64_L3_EXEC | UC64_L3_READ)
#define __S110		__pgprot(UC64_L3_EXEC | UC64_L3_WRITE)
#define __S111		__pgprot(UC64_L3_EXEC | UC64_L3_WRITE | UC64_L3_READ)

#define pte_modify(pte, newprot)	__pte({BUG(); 0; })

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
#define pmd_present(pmd)	(pmd_val(pmd) & UC64_L2_EXIST)
#define pte_present(pte)	(pte_val(pte) & UC64_L3_EXIST)

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

#define pte_write(pte)		(pte_val(pte) & UC64_L3_WRITE)
#define pte_dirty(pte)		(pte_val(pte) & UC64_L3_DIRTY)
#define pte_young(pte)		(pte_val(pte) & UC64_L3_YOUNG)
#define pte_special(pte)	(0)

#define pte_wrprotect(pte)	(__pte(pte_val(pte) & ~UC64_L3_WRITE))
#define pte_mkwrite(pte)	(__pte(pte_val(pte) | UC64_L3_WRITE))
#define pte_mkclean(pte)	(__pte(pte_val(pte) & ~UC64_L3_DIRTY))
#define pte_mkdirty(pte)	(__pte(pte_val(pte) | UC64_L3_DIRTY))
#define pte_mkold(pte)		(__pte(pte_val(pte) & ~UC64_L3_YOUNG))
#define pte_mkyoung(pte)	(__pte(pte_val(pte) | UC64_L3_YOUNG))
#define pte_mkspecial(pte)	(pte)

#define pgtable_cache_init()		do { } while (0)
#define check_pgt_cache()		do { } while (0)

#define pgd_ERROR(pgd)			pr_err("%s:%d: bad pgd %016lx.\n", \
					__FILE__, __LINE__, pgd_val(pgd))
#define pmd_ERROR(pmd)			pr_err("%s:%d: bad pmd %016lx.\n", \
					__FILE__, __LINE__, pmd_val(pmd))

#define __swp_type(x)			({BUG(); 0; })
#define __swp_offset(x)			({BUG(); 0; })
#define __swp_entry(type, offset)	((swp_entry_t){0}) /* FIXME */
#define __pte_to_swp_entry(pte)		((swp_entry_t) { pte_val(pte) })
#define __swp_entry_to_pte(swp)		((pte_t) { (swp).val })

#define pte_file(pte)			(pte_val(pte) & UC64_L3_FILE)
#define pte_to_pgoff(x)			({BUG(); 0; })
#define pgoff_to_pte(x)			__pte({BUG(); 0;})

#define PTE_FILE_MAX_BITS		36 /* FIXME */

#include <asm-generic/pgtable.h>

#endif /* __ASM_UNICORE64_PGTABLE_H__ */
