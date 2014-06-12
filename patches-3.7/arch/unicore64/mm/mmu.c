#include <linux/mm.h>
#include <linux/memblock.h>
#include <linux/sched.h>
#include <asm/cacheflush.h>
#include <asm/tlbflush.h>

#include <asm/setup_arch.h>
#include <arch/asm-mmuops.h>

/*
 * empty_zero_page is a special page that is used for
 * zero-initialized data and COW.
 */
struct page *empty_zero_page;

static void __init uc64_create_direct_mapping(phys_addr_t start,
		unsigned long length, phys_addr_t phys_pud,
		unsigned long prot_extra_flag)
{
	phys_addr_t phys;
	pgprot_t prot_pmd;
	pmd_t *pmd;

	/* ONLY SUPERPAGE supported */
	if ((start | length) & UC64_SPAGE_SELECT)
		BUG();

	/* the first pud has been written in head.S */
	prot_pmd = __pgprot(UC64_PMD_EXIST | UC64_PMD_SPAGE | UC64_PMD_RWX
			| UC64_PMD_SHARE | prot_extra_flag);
	pmd = (pmd_t *)__va(phys_pud) + pmd_index((unsigned long)__va(start));

	for (phys = start; phys < (start + length); phys += UC64_PMD_SIZE) {
		set_pmd(pmd, __pmd(phys | pgprot_val(prot_pmd)));
		pmd++;
	}
}

static void __init uc64_create_io_direct_mapping(void)
{
	phys_addr_t phys_pud00 = UC64_PM_PGTABLE_PUD_IO00;
	phys_addr_t phys_pud01 = UC64_PM_PGTABLE_PUD_IO01;
	phys_addr_t phys_io_start = __pa(UC64_VM_IO_START);
	pgprot_t prot_pud;
	pud_t *pud;

	prot_pud = __pgprot(UC64_PGD_EXIST);

	pud = (pud_t *)UC64_VM_PGTABLE_PGD
		+ pgd_index((unsigned long)UC64_VM_IO_START);
	set_pud(pud, __pud(phys_pud00 | pgprot_val(prot_pud)));
	uc64_create_direct_mapping(phys_io_start, UC64_PGD_SIZE,
			phys_pud00, UC64_PMD_TYPE_IO);

	pud++;
	phys_io_start += UC64_PGD_SIZE;
	set_pud(pud, __pud(phys_pud01 | pgprot_val(prot_pud)));
	uc64_create_direct_mapping(phys_io_start, UC64_PGD_SIZE,
			phys_pud01, UC64_PMD_TYPE_IO);
}

/*
 * paging_init() sets up the page tables, initialises the zone memory
 * maps, and sets up the zero page, bad page and bad page tables.
 */
void __init paging_init(void)
{
	struct memblock_region *reg;

	/* First 1G for direct-mapped area should be cleared. */
	swapper_pg_dir[0] = __pgd(0);

	/* Direct map all the memory banks. */
	for_each_memblock(memory, reg) {
		uc64_create_direct_mapping(reg->base, reg->size,
				UC64_PM_PGTABLE_PUD_DM00, UC64_PMD_TYPE_CACHE);
	}

	/* Set first 4M physical memory as noncached */
	uc64_create_direct_mapping(UC64_PM_NONCACHED_START,
			UC64_PM_NONCACHED_END - UC64_PM_NONCACHED_START,
			UC64_PM_PGTABLE_PUD_DM00, UC64_PMD_TYPE_NOCACHE);

	uc64_create_io_direct_mapping();

	__invalid_tlb();

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
	/* It's too slow to use flush_tlb_mm(vma->vm_mm) */
	__invalid_tlb();
}
