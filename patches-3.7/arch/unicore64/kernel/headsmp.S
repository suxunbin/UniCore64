#include <linux/linkage.h>
#include <linux/init.h>

#include <arch/hwdef-memory.h>
#include <arch/asm-mmuops.h>
#include <arch/head-macros.S>

	__HEAD
ENTRY(secondary_stext)
	__head_init
	__cache_init

	dmovl		r0, #UC64_PM_PGTABLE_PGD
	__set_pgd	r0

	dmovl		r1, #UC64_PM_PGTABLE_PGD
	dmovl		r0, #UC64_PM_PGTABLE_PUD_DM00
	dor		r0, r0, #UC64_PGD_EXIST
	std		r0, [r1]

	__invalid_tlb

	__enable_mmu

	/* Use our vector table*/
	ldd		r0, =__vectors_table
	movc		CP0_VECBASE, r0, #0

	movc		r0, CP0_INTR, #0
	dandn		r0, r0, #CP0_INTR_IK2
	movc		CP0_INTR, r0, #0

	ldd		r0, =secondary_stack_start
	ldd		sp, [r0]
	ldd		r0, =secondary_start_kernel
	jump		r0
ENDPROC(secondary_stext)
