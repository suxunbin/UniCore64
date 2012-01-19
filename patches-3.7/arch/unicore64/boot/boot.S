#include <arch/hwdef-memory.h>
#include <arch/hwdef-copro.h>
#include <arch/asm-common.h>
#include <arch/asm-mmuops.h>
#include <arch/head-macros.S>

	.section ".start"
	.globl	_start
_start:
	/*
	 * Initialize ASR and coprocessor 0.
	 */
	__head_initialize	r0

	/*
	 * Initialise TLB and Caches.
	 */
	__invalid_dcache	r0
	__invalid_icache	r0
	__invalid_tlb		r0

	/*
	 * Turn on dcache and icache.
	 */
	uc64_enable_cache	r0

	/*
	 * Set the sp register.
	 */
	dmovl	sp, #UC64_PM_ZIMAGE_STACKTOP

	/*
	 * Clear BSS region.
	 */
	__head_clear_bss

#ifdef CONFIG_ARCH_FPGA
	/*
	 * Prepare early devtree for fpga board.
	 */
	dmovl	r0, #UC64_PM_DTB_START
	adr	r1, dtb_data
	dmovl	r2, #dtb_data_end - dtb_data
	call	memcpy
#endif /* CONFIG_ARCH_FPGA */

	/*
	 * Call decompress_kernel, and it's three parameters are:
	 *   r0: output_start
	 *   r1: free_mem_ptr_p
	 *   r2: free_mem_ptr_end_p
	 */
	dmovl	r0, #UC64_PM_KIMAGE_START
	dmovl	r1, #UC64_PM_ZIMAGE_STACKTOP
	dmovl	r2, #UC64_PM_ZIMAGE_HEAP_END
	call	decompress_kernel

	/*
	 * Flush the cache to maintain consistency.
	 */
	__flush_dcache	r0

	/*
	 * Initialize ASR and coprocessor 0.
	 */
	__head_initialize	r0

	/*
	 * Jump to the start address of kernel image.
	 */
	dmovl	r0, #UC64_VM_KIMAGE_START
	jump	r0

	.section .rodata.dtb
	__epip4d_align64
dtb_data:
	.incbin "arch/unicore64/boot/unicore64-fpga.dtb"
dtb_data_end:

	.section .rodata.piggy
	__epip4d_align64
	.globl	input_data
input_data:
	.incbin "arch/unicore64/boot/piggy.bin"
	.globl	input_data_end
input_data_end: