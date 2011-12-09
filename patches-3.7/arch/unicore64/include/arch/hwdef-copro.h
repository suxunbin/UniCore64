#ifndef __UNICORE64_ARCH_HWDEF_COPRO_H__
#define __UNICORE64_ARCH_HWDEF_COPRO_H__

#include <arch/bitfield.h>

/**
 * DOC: HWDEF_COPRO_H
 *
 * This file defines coprocessor names and their register names.
 *
 * \\\\lt:programlisting\\\\gt:
 * -
 * cp0 is the control coprocesscor which helps the main processor
 * with global control.
 * -
 * CP0 CR0:	register that stores CPU information, Cache information
 *		and processor ID
 * CP0 CR1:	control register of mmu and Cache
 * CP0 CR2:	register for Translation Table Base and Address Space
 *		Identifier
 * CP0 CR3:	register for status information of instruction
 *		and data abort
 * CP0 CR4:	register for virtual address of data abort
 * CP0 CR5:	register for TLB management
 * CP0 CR6:	register for DCache management
 * CP0 CR7:	register for ICache management
 * CP0 CR8:	register for Memory Region Attribute Register
 *		configuration
 * CP0 CR9:	register for interruption vector base
 * CP0 CR10:	register for timer interrupt and interrupt information
 *		such as	number, type and priority
 * CP0 CR11:	control register of Read/Write Margin
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
 * DOC: CP0 CR1 bits
 * \\\\lt:programlisting\\\\gt:
 * CR1 bits (CP#0 CR1)
 * CP0_CTRLREG_MMU:		MMU enable
 * CP0_CTRLREG_ALIGN:		Alignment abort enable
 * CP0_CTRLREG_DCACHE:		Dcache enable
 * CP0_CTRLREG_ICACHE:		Icache enable
 * CP0_CTRLREG_SAVEPOWER:	Save power enable
 * CP0_CTRLREG_WRITEBACK:	Dcache write mechanism: write back
 * \\\\lt:/programlisting\\\\gt:
 */
#define CP0_CTRLREG_MMU			FIELD(1, 1, 0)
#define CP0_CTRLREG_ALIGN		FIELD(1, 1, 1)
#define CP0_CTRLREG_DCACHE		FIELD(1, 1, 2)
#define CP0_CTRLREG_ICACHE		FIELD(1, 1, 3)
#define CP0_CTRLREG_SAVEPOWER		FIELD(1, 1, 4)
#define CP0_CTRLREG_WRITEBACK		FIELD(1, 1, 5)

/**
 * DOC: CP0 CPUID information
 * \\\\lt:programlisting\\\\gt:
 * CP0_CPUID_PARTNO_MASK:	mask for the cpuid partnumber
 * CP0_CPUID_PARTNO_PKUNITY:	the cpuid partnumber of PKUnity
 * CP0_CPUID_LAYOUT_MASK:	mask for the cpuid layout
 * CP0_CPUID_SERIES_MASK:	mask for the cpuid series
 * CP0_CPUID_DESIGNER_MASK:	mask for the cpuid designer
 * CP0_CPUID_DESIGNER_MPRC:	the symbol of MPRC for the cpu designer
 * \\\\lt:/programlisting\\\\gt:
 */
#define CP0_CPUID_PARTNO_MASK		FMASK(16, 0)
#define CP0_CPUID_PARTNO_PKUNITY	FIELD(0x863, 12, 0)
#define CP0_CPUID_LAYOUT_MASK		FMASK(4, 16)
#define CP0_CPUID_SERIES_MASK		FMASK(4, 20)
#define CP0_CPUID_DESIGNER_MASK		FMASK(8, 24)
#define CP0_CPUID_DESIGNER_MPRC		FIELD(0x4D, 8, 24)

#endif /* __UNICORE64_ARCH_HWDEF_COPRO_H__ */
