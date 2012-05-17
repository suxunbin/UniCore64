#include <linux/mm.h>
#include <linux/memblock.h>
#include <linux/sched.h>

#include <asm/setup_arch.h>

/*
 * empty_zero_page is a special page that is used for
 * zero-initialized data and COW.
 */
struct page *empty_zero_page;

static void __init uc64_create_direct_mapping(phys_addr_t start,
		unsigned long length)
{
	phys_addr_t phys;
	phys_addr_t phys_pud = UC64_PM_PGTABLE_PUD_DM00;
	pgprot_t prot_pmd;
	pmd_t *pmd;

	/* ONLY SUPERPAGE supported */
	if ((start | length) & UC64_SPAGE_SELECT)
		BUG();

	/* the first pud has been written in head.S */
	prot_pmd = __pgprot(UC64_PMD_TYPE_CACHE | UC64_PMD_EXIST
			| UC64_PMD_RWX | UC64_PMD_SPAGE);
	pmd = (pmd_t *)(phys_pud) + pmd_index((unsigned long)__va(start));

	for (phys = start; phys < (start + length); phys += UC64_PMD_SIZE) {
		set_pmd(pmd, __pmd(phys | pgprot_val(prot_pmd)));
		pmd++;
	}
}

/*
 * paging_init() sets up the page tables, initialises the zone memory
 * maps, and sets up the zero page, bad page and bad page tables.
 */
void __init paging_init(void)
{
	struct memblock_region *reg;

	/* First 1G for direct-mapped area has been cleared. */

	/* Direct map all the memory banks. */
	for_each_memblock(memory, reg) {
		uc64_create_direct_mapping(reg->base, reg->size);
	}

	/* Initialize the zero page. */
	memset((void *)UC64_VM_ZEROPAGE, 0, PAGE_SIZE);
	empty_zero_page = virt_to_page(UC64_VM_ZEROPAGE);

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
