#include <linux/mm.h>
#include <linux/kernel.h>
#include <asm/tlbflush.h>
#include <arch/asm-mmuops.h>

/**
 * flush_tlb_mm() -
 * @mm
 */
void flush_tlb_mm(struct mm_struct *mm)
{
	__invalid_tlb();
}

/**
 * flush_tlb_page() -
 * @vma:
 * @va:
 */
void flush_tlb_page(struct vm_area_struct *vma, unsigned long va)
{
	/* FIXME */
	BUG();
}


/**
 * flush_tlb_range() -
 * @vma:
 * @start:
 * @end:
 */
void flush_tlb_range(struct vm_area_struct *vma,
		     unsigned long start, unsigned long end)
{
	/* FIXME */
	BUG();
}

/**
 * flush_tlb_kernl_range() -
 * @start:
 * @end:
 */
void flush_tlb_kernel_range(unsigned long start, unsigned long end)
{
	/* FIXME */
	BUG();
}
