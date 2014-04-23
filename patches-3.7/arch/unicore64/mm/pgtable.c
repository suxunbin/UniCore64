#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/mm.h>
#include <asm/pgtable.h>

/**
 * pgd_alloc() - Allocates a new Page Global Directory
 * @mm:
 */
pgd_t *pgd_alloc(struct mm_struct *mm)
{
	pgd_t *new_pgd = (pgd_t *)__get_free_page(GFP_KERNEL | __GFP_ZERO);

	if (new_pgd)
		copy_page(new_pgd, swapper_pg_dir);

	return new_pgd;
}

/**
 * pgd_free() - Release a page table and insert the freed page frame in cache
 * @mm:
 * @pgd:
 */
void pgd_free(struct mm_struct *mm, pgd_t *pgd)
{
	free_page((unsigned long)pgd);
}

/**
 * pte_free() - Free page immediately
 * @mm:
 * @p:
 *
 * This function is used in __pte_alloc if we raced with another
 * process).  We have to correct whatever pte_alloc_one() did before
 * returning the pages to the allocator.
 */
void pte_free(struct mm_struct *mm, struct page *p)
{
	pgtable_page_dtor(p);
	__free_page(p);
}

/**
 * pte_free_kernel() - Free page immediately
 * @mm:
 * @p:
 */
void pte_free_kernel(struct mm_struct *mm, pte_t *p)
{
	if(p) {
		free_page((unsigned long)p);
	}
}

/**
 * pte_alloc_one() - Return the address of page table entry
 * @mm:
 * address:
 *
 * Receives as parameters the address of a Page Middle Directory entry p and
 * a linear address a, and it returns the address of the Page Table entry
 * corresponding to a. If the Page Middle Directory entry is null,
 * the function must allocate a new Page Table
 */
pgtable_t pte_alloc_one(struct mm_struct *mm, unsigned long address)
{
	struct page *pte = alloc_page(GFP_KERNEL | __GFP_ZERO);

	if (pte)
		pgtable_page_ctor(pte);

	return pte;
}

/**
 * pte_alloc_one_kernel() - Return the address of a page table entry
 * @mm:
 * @address:
 *
 * This function is the simaller to pte_alloc_one,and used by kernel only
 */
pte_t *pte_alloc_one_kernel(struct mm_struct *mm, unsigned long address)
{
	pte_t *pte;
	struct page *page;
	page  = alloc_page(GFP_KERNEL | __GFP_ZERO);

	pte = (pte_t *)page_address(page);

	return pte;
}

/**
 * set_pte() - sets the given PTE
 * @ptep:
 * @pte:
 *
 * This function also sanity-checks the requested PTE against the page
 * homecaching.  Unspecified parts of the PTE are filled in when it is
 * written to memory, i.e. all caching attributes if "!forcecache",
 * or the home cpu if "anyhome".
 */
void set_pte(pte_t *ptep, pte_t pte)
{
	*(ptep) = pte;
}

/**
 * pud_populate() - Allocate and initialize the kernel pmds
 * @mm:
 * pmd:
 */
void pud_populate(struct mm_struct *mm, pud_t *pudp, pmd_t *pmd)
{
	set_pud(pudp, __pud(__pa(pmd) | UC64_PGD_EXIST));
}

/**
 * pmd_populate() -
 * @mm:
 * @pmd:
 * @page:
 */
void pmd_populate(struct mm_struct *mm, pmd_t *pmd, pgtable_t page)
{
	set_pmd(pmd, __pmd(page_to_phys(page) | UC64_PMD_EXIST
		| UC64_PMD_SHARE));
}

/**
 * pmd_populate_kernel() -
 * @mm:
 * @pmd:
 * @ptep:
 */
void pmd_populate_kernel(struct mm_struct *mm, pmd_t *pmd, pte_t *ptep)
{
	set_pmd(pmd, __pmd(__pa((unsigned long)ptep) | UC64_PMD_EXIST));
}

/**
 * pmd_alloc_one() -
 * @mm:
 * @addr:
 */
pmd_t *pmd_alloc_one(struct mm_struct *mm, unsigned long addr)
{
	return (pmd_t *)__get_free_page(GFP_KERNEL | __GFP_ZERO);
}

/**
 * pmd_free() -
 * @mm:
 * @pmdp:
 */
void pmd_free(struct mm_struct *mm, pmd_t *pmdp)
{
	free_page((unsigned long)pmdp);
}
