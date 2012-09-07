#include <linux/of_fdt.h>
#include <linux/memblock.h>

void * __init early_init_dt_alloc_memory_arch(u64 size, u64 align)
{
	return __va(memblock_alloc(size, align));
}

void __init early_init_dt_add_memory_arch(u64 base, u64 size)
{
	memblock_add(base, size);
}

#ifdef CONFIG_BLK_DEV_INITRD
void __init early_init_dt_setup_initrd_arch(unsigned long start,
					    unsigned long end)
{
	/* FIXME */
	BUG();
}
#endif

/**
 * irq_create_of_mapping - Hook to resolve OF irq specifier into a Linux irq#
 * @controller:
 * @intspec:
 * @intsize:
 *
 * Currently the mapping mechanism is trivial; simple flat hwirq numbers are
 * mapped 1:1 onto Linux irq numbers.  Cascaded irq controllers are not
 * supported.
 */
unsigned int irq_create_of_mapping(struct device_node *controller,
				   const u32 *intspec, unsigned int intsize)
{
	return intspec[0];
}

void __init setup_arch_devtree(char *cmdline)
{
	initial_boot_params = (void *)UC64_VM_DTB_START;
	of_scan_flat_dt(early_init_dt_scan_chosen, cmdline);
	of_scan_flat_dt(early_init_dt_scan_root, NULL);
	of_scan_flat_dt(early_init_dt_scan_memory, NULL);
}
