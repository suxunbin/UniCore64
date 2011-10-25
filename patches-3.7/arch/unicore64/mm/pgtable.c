#include <linux/mm.h>

/**
 * pgd_alloc() - Allocates a new Page Global Directory
 * @mm:
 */
pgd_t *pgd_alloc(struct mm_struct *mm)
{
	/* FIXME */
	BUG();
}

/**
 * pgd_free() - Release a page table and insert the freed page frame in cache
 * @mm:
 * @pgd:
 */
void pgd_free(struct mm_struct *mm, pgd_t *pgd)
{
	/* FIXME */
	BUG();
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
	/* FIXME */
	BUG();
}

/**
 * pte_free_kernel() - Free page immediately
 * @mm:
 * @p:
 */
void pte_free_kernel(struct mm_struct *mm, pte_t *p)
{
	/* FIXME */
	BUG();
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
	/* FIXME */
	BUG();
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
	/* FIXME */
	BUG();
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
	/* FIXME */
	BUG();
}

/**
 * pud_populate() - Allocate and initialize the kernel pmds
 * @mm:
 * pmd:
 */
void pud_populate(struct mm_struct *mm, pud_t *pudp, pmd_t *pmd)
{
	/* FIXME */
	BUG();
}
