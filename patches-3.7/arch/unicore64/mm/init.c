#include <linux/kernel.h>
#include <linux/memblock.h>
#include <linux/bootmem.h>

#include <asm/sections.h>
#include <asm/setup_arch.h>

/**
 * mem_init() -
 */
void __init mem_init(void)
{
	/* FIXME */
	BUG();
}

/**
 * free_initmem() -
 */
void free_initmem(void)
{
	/* FIXME */
	BUG();
}

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
	unsigned long last_pfn;

	/* Find the PFN for the last page in the system. */
	for_each_memblock(memory, reg) {
		last_pfn = memblock_region_memory_end_pfn(reg);
		if (max_pfn < last_pfn)
			max_pfn = last_pfn;
	}
}

void __init setup_arch_memory(void)
{
	memblock_init();
	max_pfn_init();
	paging_init();
	zone_sizes_init();
}
