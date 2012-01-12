#include <linux/kernel.h>
#include <linux/memblock.h>

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

void __init setup_arch_memory(void)
{
	/* Reserve the kernel text, kernel data and initrd with memblock. */
	memblock_reserve(__pa(_text), _end - _text);

	/* Reserve the page tables. */
	memblock_reserve(__pa(swapper_pg_dir), PAGE_SIZE);

	memblock_allow_resize();
	memblock_dump_all();

	paging_init();
}
