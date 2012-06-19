#include <linux/kernel.h>
#include <linux/memblock.h>
#include <linux/bootmem.h>

#include <asm/sections.h>
#include <asm/setup_arch.h>

/**
 * mem_init() - release free pages to the buddy allocator
 * Returns the number of pages actually released.
 */
void __init mem_init(void)
{
	max_mapnr = pfn_to_page(max_pfn) - mem_map;

	totalram_pages += free_all_bootmem();
}

/**
 * free_initmem() -
 */
void free_initmem(void)
{
	/* FIXME */
	BUG();
}

#ifdef CONFIG_BLK_DEV_INITRD
void free_initrd_mem(unsigned long start, unsigned long end)
{
	/* FIXME */
	BUG();
}
#endif

static void __init zone_sizes_init(void)
{
	unsigned long zone_sizes[MAX_NR_ZONES];

	/* Initialize each of zones. */
	memset(zone_sizes, 0, sizeof(zone_sizes));
	zone_sizes[ZONE_NORMAL] = max_pfn;

	/* Initialize mem_map[] */
	free_area_init(zone_sizes);
}

static void __init memblock_init(void)
{
	/* Reserve the kernel text, kernel data and initrd with memblock. */
	memblock_reserve(__pa(_text), _end - _text);

	/* Reserve the page tables. */
	memblock_reserve(__pa(swapper_pg_dir), PAGE_SIZE);

	memblock_allow_resize();
	memblock_dump_all();
}

static void __init max_pfn_init(void)
{
	struct memblock_region *reg;
	unsigned long start_pfn, last_pfn;

	/*
	 * Find the first and last PFN for low memory, and
	 * the PFN for the last page in the system.
	 */
	min_low_pfn = -1UL;
	for_each_memblock(memory, reg) {
		start_pfn = memblock_region_memory_base_pfn(reg);
		last_pfn = memblock_region_memory_end_pfn(reg);
		if (min_low_pfn > start_pfn)
			min_low_pfn = start_pfn;
		if (max_low_pfn < last_pfn)
			max_low_pfn = last_pfn;
	}
	max_pfn = max_low_pfn;
}

void __init setup_arch_memory(void)
{
	memblock_init();
	max_pfn_init();
	paging_init();
	zone_sizes_init();
}
