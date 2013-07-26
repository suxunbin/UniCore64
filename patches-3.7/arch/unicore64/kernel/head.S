/**
 * DOC: KERNEL_HEAD_S
 * This file write level-one and level-two page table to map the first 64MB
 * of kernel image, then turn mmu on, and finally jump to start_kernel.
 */
#include <linux/linkage.h>
#include <linux/init.h>

#include <asm/thread_info.h>

#include <arch/hwdef-pgtable.h>
#include <arch/hwdef-memory.h>
#include <arch/hwdef-cpu.h>
#include <arch/hwdef-copro.h>
#include <arch/asm-mmuops.h>
#include <arch/head-macros.S>

/**
 * DOC: swapper_pg_dir
 * swapper_pg_dir is the virtual address of the initial page table.
 */
	.globl		swapper_pg_dir
	.equ		swapper_pg_dir, UC64_VM_PGTABLE_PGD

/**
 * stext - Kernel startup entry point.
 * This is normally called from the decompressed code.
 * The requirements are: MMU = off, IRQS = off
 */
	__HEAD
ENTRY(stext)
	__head_init
	__cache_init

	/*
	 * Enable the MMU.  This completely changes the structure of the visible
	 * memory space.  You will not be able to trace execution through this.
	 */
	dmovl		sp, #UC64_PM_ZIMAGE_STACKTOP
	call		__head_pgtable_init

	__invalid_tlb

	__enable_mmu

	ldd		sp, __priv_sp

	__clear_bss

	/* We must get the VA of start_kernel, and avoid using RA. */
	ldd		r0, =start_kernel
	jump		r0
ENDPROC(stext)

	____align64
__priv_sp:
	.dword		init_thread_union + (THREAD_SIZE - 8)

/**
 * __head_pgtable_init - initialize the level one and level two page table
 * it will map the first 64MB of kernel image
 */
ENTRY(__head_pgtable_init)
	__push		lr
	/*
	 * Step one: clear 4k level-one page table for pgd
	 */
	dmovl		r0, #UC64_PM_PGTABLE_PGD
	dmov		r1, #0
	dmovl		r2, #UC64_PAGE_SIZE
	call		memset

	/*
	 * Step two: write level-one page table
	 * Level one page table entry value = level two page table base + offset
	 */
	dmovl		r1, #UC64_VM_DMAP_START
	dasr		r1, r1, #UC64_PGD_SHIFT
	dlsl		r1, r1, #UC64_PGTBL_ENTRY_BITS
	dmovl		r2, #UC64_PAGE_SELECT
	dand		r1, r1, r2
	dmovl		r2, #UC64_PM_PGTABLE_PGD
	dadd		r1, r1, r2
	dmovl		r0, #UC64_PM_PGTABLE_PUD_DM00
	dor		r0, r0, #UC64_PGD_EXIST
	std		r0, [r1]

	dmovl		r1, #UC64_PM_PGTABLE_PGD
	dmovl		r0, #UC64_PM_PGTABLE_PUD_DM00
	dor		r0, r0, #UC64_PGD_EXIST
	std		r0, [r1]

	/*
	 * Step three: clear 4k level-two page table from first
	 * direct-mapped pmd
	 */
	dmovl		r0, #UC64_PM_PGTABLE_PUD_DM00
	dmov		r1, #0
	dmovl		r2, #UC64_PAGE_SIZE
	call		memset

	/*
	 * Step four: direct map 64M PM2VM in level two page table
	 * Level two page table entry value = physcial frame number + offset
	 * offset: S=0, MA=10, G=0, RWX=111, M=0, A=0, E=1, US=0, PT=1
	 */
	dmovl		r1, #UC64_PM_PGTABLE_PUD_DM00
	dmovl		r0, UC64_PM_START
	dor		r0, r0, #UC64_PMD_SPAGE | UC64_PMD_EXIST
	dor		r0, r0, #UC64_PMD_TYPE_CACHE | UC64_PMD_RWX
	dmovl		r2, #UC64_PMD_SHARE
	dor		r0, r0, r2
	dmovl		r2, UC64_PMD_SIZE

	.rep		32
	std.w		r0, [r1]+, #8
	dadd		r0, r0, r2
	.endr

	/*
	 * Step five: set pgd register in cp0
	 */
	dmovl		r0, #UC64_PM_PGTABLE_PGD
	__set_pgd	r0

	__pop		lr
	return
ENDPROC(__head_pgtable_init)
