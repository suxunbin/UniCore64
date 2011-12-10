#ifndef __UNICORE64_ARCH_HWDEF_COPRO_H__
#define __UNICORE64_ARCH_HWDEF_COPRO_H__

/**
 * DOC: HWDEF_COPRO_H
 *
 * This file defines coprocessor names and their register names.
 */
#include <arch/bitfield.h>

/**
 * DOC: HWDEF_COPRO_H_CP0
 *
 * CP0 is the control coprocesscor which helps the main processor
 * with global control.
 *
 * Following CP0 register names are defined:
 *
 * \\\\lt:programlisting\\\\gt:
 * -
 * CP0 CR0:	reg. that stores CPU information and cache information
 * CP0 CR1:	control reg. of mmu and Cache
 * CP0 CR2:	reg. for Translation Table Base and Address Space Identifier
 * CP0 CR3:	reg. for status information of instruction and data abort
 * CP0 CR4:	reg. for virtual address of data abort
 * CP0 CR5:	reg. for TLB management
 * CP0 CR6:	reg. for DCache management
 * CP0 CR7:	reg. for ICache management
 * CP0 CR8:	reg. for Memory Region Attribute Register configuration
 * CP0 CR9:	reg. for interruption vector base
 * CP0 CR10:	reg. for timer interrupt and interrupt information
 * CP0 CR11:	control reg. of Read/Write Margin
 * -
 * \\\\lt:/programlisting\\\\gt:
 */
#define CP0_CPUID		p0.c0
#define CP0_CTRLREG		p0.c1
#define CP0_TTB_ASID		p0.c2
#define CP0_ABORT_STAT		p0.c3
#define CP0_DABORT_VADDR	p0.c4
#define CP0_TLB			p0.c5
#define CP0_DCACHE		p0.c6
#define CP0_ICACHE		p0.c7
#define CP0_MRAR		p0.c8
#define CP0_INTR_VECBASE	p0.c9
#define CP0_INTR_STAT		p0.c10
#define CP0_RWM			p0.c11

/**
 * DOC: HWDEF_COPRO_H_CP0_CTRLREG
 * Following bit field definitions for control register in CP0 are defined:
 *
 * \\\\lt:programlisting\\\\gt:
 * -
 * CP0_CTRLREG_MMU:		MMU enable
 * CP0_CTRLREG_ALIGN:		Alignment abort enable
 * CP0_CTRLREG_DCACHE:		Dcache enable
 * CP0_CTRLREG_ICACHE:		Icache enable
 * CP0_CTRLREG_SAVEPOWER:	Save power enable
 * CP0_CTRLREG_WRITEBACK:	Dcache write mechanism: write back
 * -
 * \\\\lt:/programlisting\\\\gt:
 */
#define CP0_CTRLREG_MMU			BFIELD(1, 1, 0)
#define CP0_CTRLREG_ALIGN		BFIELD(1, 1, 1)
#define CP0_CTRLREG_DCACHE		BFIELD(1, 1, 2)
#define CP0_CTRLREG_ICACHE		BFIELD(1, 1, 3)
#define CP0_CTRLREG_SAVEPOWER		BFIELD(1, 1, 4)
#define CP0_CTRLREG_WRITEBACK		BFIELD(1, 1, 5)

/**
 * DOC: HWDEF_COPRO_H_CP0_CPUID
 * Following cpu inforamtion macros in CP0 are defined:
 *
 * \\\\lt:programlisting\\\\gt:
 * -
 * CP0_CPUID_PARTNO_MASK:	mask for the cpuid partnumber
 * CP0_CPUID_PARTNO_PKUNITY:	the cpuid partnumber of PKUnity
 * CP0_CPUID_LAYOUT_MASK:	mask for the cpuid layout
 * CP0_CPUID_SERIES_MASK:	mask for the cpuid series
 * CP0_CPUID_DESIGNER_MASK:	mask for the cpuid designer
 * CP0_CPUID_DESIGNER_MPRC:	the symbol of MPRC for the cpu designer
 * -
 * \\\\lt:/programlisting\\\\gt:
 */
#define CP0_CPUID_PARTNO_MASK		BFMASK(16, 0)
#define CP0_CPUID_PARTNO_PKUNITY	BFIELD(0x863, 12, 0)
#define CP0_CPUID_LAYOUT_MASK		BFMASK(4, 16)
#define CP0_CPUID_SERIES_MASK		BFMASK(4, 20)
#define CP0_CPUID_DESIGNER_MASK		BFMASK(8, 24)
#define CP0_CPUID_DESIGNER_MPRC		BFIELD(0x4D, 8, 24)

#endif /* __UNICORE64_ARCH_HWDEF_COPRO_H__ */
