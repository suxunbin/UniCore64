#include <linux/mm.h>
#include <linux/memblock.h>

#include <asm/setup_arch.h>

/*
 * empty_zero_page is a special page that is used for
 * zero-initialized data and COW.
 */
struct page *empty_zero_page;

/*
 * paging_init() sets up the page tables, initialises the zone memory
 * maps, and sets up the zero page, bad page and bad page tables.
 */
void __init paging_init(void)
{
	/* Initialize the zero page. */
	memset((void *)UC64_VM_ZEROPAGE, 0, PAGE_SIZE);
	empty_zero_page = virt_to_page(UC64_VM_ZEROPAGE);

	/* FIXME*/
	BUG();
}

/**
 * update_mmu_cache() - checks the page table entry for validity
 * @vma:
 * @adddr:
 * @ptep:
 *
 * Take care of architecture specific things when placing a new PTE into
 * a page table, or changing an existing PTE.  Basically, there are two
 * things that we need to take care of:
 *
 *  1. If PG_dcache_clean is not set for the page, we need to ensure
 *     that any cache entries for the kernels virtual memory
 *     range are written back to the page.
 *  2. If we have multiple shared mappings of the same space in
 *     an object, we need to deal with the cache aliasing issues.
 *
 * Note that the pte lock will be held.
 */
void update_mmu_cache(struct vm_area_struct *vma, unsigned long addr,
	pte_t *ptep)
{
	/* FIXME */
	BUG();
}
