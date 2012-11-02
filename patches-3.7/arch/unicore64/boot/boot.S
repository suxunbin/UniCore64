#include <arch/hwdef-memory.h>
#include <arch/hwdef-copro.h>
#include <arch/asm-common.h>
#include <arch/asm-mmuops.h>
#include <arch/head-macros.S>

	.section	".start"
	.globl		_start
_start:
	__head_init
	__cache_init

	dmovl		sp, #UC64_PM_ZIMAGE_STACKTOP

	__clear_bss

#ifdef CONFIG_ARCH_FPGA
	/*
	 * Prepare early devtree for fpga board.
	 */
	dmovl		r0, #UC64_PM_DTB_START
	ldd		r1, =dtb_data
	ldd		r2, =dtb_data_end
	dsub		r2, r2, r1
	call		memcpy
#endif /* CONFIG_ARCH_FPGA */

	dmovl		r0, #UC64_PM_KIMAGE_START
	call		decompress_kernel

	/* Re-initialize to system default status */
	__flush_dcache
	__head_init

	/*
	 * Jump to the start address of kernel image.
	 */
	dmovl		r0, #UC64_PM_KIMAGE_START
	jump		r0

	.section	.rodata.dtb
	____align64
dtb_data:
	.incbin		"arch/unicore64/boot/unicore64-fpga.dtb"
dtb_data_end:

	.section	.rodata.piggy
	____align64
	.globl		input_data
input_data:
	.incbin		"arch/unicore64/boot/piggy.bin"
	.globl		input_data_end
input_data_end:
