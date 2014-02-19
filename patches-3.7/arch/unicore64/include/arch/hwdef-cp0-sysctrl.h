#ifndef __UNICORE64_ARCH_HWDEF_CP0_SYSCTRL_H__
#define __UNICORE64_ARCH_HWDEF_CP0_SYSCTRL_H__

#include <arch/hwdef-copro.h>

/**
 * DOC: HWDEF_CP0_SYSCTRL_H_CP0
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
 * CP0 CR4:	reg. for return address of exceptions
 * CP0 CR5:	reg. for TLB management
 * CP0 CR6:	reg. for DCache management
 * CP0 CR7:	reg. for ICache management
 * CP0 CR8:	reg. for Memory Region Attribute Register configuration
 * CP0 CR9:	reg. for interruption vector base
 * CP0 CR10:	reg. for timer interrupt and interrupt information
 * CP0 CR11:	control reg. of Read/Write Margin
 * CP0 CR12:	reg. of SysU (first 8 regs just for software use)
 *   #0: for atomic operation, saved/restored when context switch
 *   #4: for temperary usage, perhaps destroyed when context switch
 *   #5: for temperary usage, perhaps destroyed when context switch
 *   #6: reserved for ocd
 *   #7: reserved for ocd
 *   #8: physical address for last memory access
 * -
 * \\\\lt:/programlisting\\\\gt:
 */
#define CP0_CPUID		p0.c0
#define CP0_CTRLREG		p0.c1
#define CP0_TTB_ASID		p0.c2
#define CP0_TRAPSTAT		p0.c3
#define CP0_TRAPADDR		p0.c4
#define CP0_TLB			p0.c5
#define CP0_DCACHE		p0.c6
#define CP0_ICACHE		p0.c7
#define CP0_MRAR		p0.c8
#define CP0_VECBASE		p0.c9
#define CP0_INTR		p0.c10
#define CP0_RWMARGIN		p0.c11
#define CP0_SYSU		p0.c12

#define CP0_INTR_ITM			__BF(1, 1, 7)
#define CP0_INTR_LSU			__BF(1, 1, 8)
#define CP0_INTR_IK1			__BF(1, 1, 9)
#define CP0_INTR_IK2			__BF(1, 1, 10)
#define CP0_INTR_IK3			__BF(1, 1, 11)
#define CP0_INTR_IK4			__BF(1, 1, 12)
#define CP0_INTR_IPM			__BF(1, 1, 13)
#define CP0_INTR_SMP			__BS(4, 9)

/**
 * DOC: HWDEF_CP0_SYSCTRL_H_CP0_CTRLREG
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
 * CP0_CTRLREG_DEFAULT:		MMU control register's default value
 * -
 * \\\\lt:/programlisting\\\\gt:
 */
#define CP0_CTRLREG_MMU			__BF(1, 1, 0)
#define CP0_CTRLREG_ALIGN		__BF(1, 1, 1)
#define CP0_CTRLREG_DCACHE		__BF(1, 1, 2)
#define CP0_CTRLREG_ICACHE		__BF(1, 1, 3)
#define CP0_CTRLREG_SAVEPOWER		__BF(1, 1, 4)
#define CP0_CTRLREG_WRITEBACK		__BF(1, 1, 5)
#define CP0_CTRLREG_DEFAULT		CP0_CTRLREG_WRITEBACK

/**
 * DOC: HWDEF_CP0_SYSCTRL_H_CP0_CPUID
 * Following cpu inforamtion macros in CP0 are defined:
 *
 * \\\\lt:programlisting\\\\gt:
 * -
 * CP0_CPUID_PARTNO_SELECT:	mask for the cpuid partnumber
 * CP0_CPUID_PARTNO_PKUNITY:	the cpuid partnumber of PKUnity
 * CP0_CPUID_LAYOUT_SELECT:	mask for the cpuid layout
 * CP0_CPUID_SERIES_SELECT:	mask for the cpuid series
 * CP0_CPUID_DESIGNER_SELECT:	mask for the cpuid designer
 * CP0_CPUID_DESIGNER_MPRC:	the symbol of MPRC for the cpu designer
 * -
 * \\\\lt:/programlisting\\\\gt:
 */
#define CP0_CPUID_PARTNO_SELECT		__BS(16, 0)
#define CP0_CPUID_PARTNO_PKUNITY	__BF(0x863, 12, 0)
#define CP0_CPUID_LAYOUT_POS		(16)
#define CP0_CPUID_LAYOUT_SELECT		__BS(4, CP0_CPUID_LAYOUT_POS)
#define CP0_CPUID_SERIES_POS		(20)
#define CP0_CPUID_SERIES_SELECT		__BS(4, CP0_CPUID_SERIES_POS)
#define CP0_CPUID_DESIGNER_SELECT	__BS(8, 24)
#define CP0_CPUID_DESIGNER_MPRC		__BF(0x4D, 8, 24)

/**
 * DOC: HWDEF_CP0_SYSCTRL_H_CP0_CACHE
 * Following cache inforamtion macros in CP0 are defined.
 */
#define CP0_CPUID_ICACHE_LINE_SELECT		__BS(2, 0)
#define CP0_CPUID_ICACHE_LINE_8BYTE		__BF(0, 2, 0)
#define CP0_CPUID_ICACHE_LINE_16BYTE		__BF(1, 2, 0)
#define CP0_CPUID_ICACHE_LINE_32BYTE		__BF(2, 2, 0)
#define CP0_CPUID_ICACHE_LINE_64BYTE		__BF(3, 2, 0)

#define CP0_CPUID_ICACHE_ASSOC_SELECT		__BS(3, 3)
#define CP0_CPUID_ICACHE_ASSOC_DMAP		__BF(0, 3, 3)
#define CP0_CPUID_ICACHE_ASSOC_2WAY		__BF(1, 3, 3)
#define CP0_CPUID_ICACHE_ASSOC_4WAY		__BF(2, 3, 3)
#define CP0_CPUID_ICACHE_ASSOC_8WAY		__BF(3, 3, 3)
#define CP0_CPUID_ICACHE_ASSOC_16WAY		__BF(4, 3, 3)
#define CP0_CPUID_ICACHE_ASSOC_32WAY		__BF(5, 3, 3)
#define CP0_CPUID_ICACHE_ASSOC_64WAY		__BF(6, 3, 3)
#define CP0_CPUID_ICACHE_ASSOC_128WAY		__BF(7, 3, 3)

#define CP0_CPUID_ICACHE_SIZE_SELECT		__BS(3, 6)
#define CP0_CPUID_ICACHE_SIZE_512B		__BF(0, 3, 6)
#define CP0_CPUID_ICACHE_SIZE_1KB		__BF(1, 3, 6)
#define CP0_CPUID_ICACHE_SIZE_2KB		__BF(2, 3, 6)
#define CP0_CPUID_ICACHE_SIZE_4KB		__BF(3, 3, 6)
#define CP0_CPUID_ICACHE_SIZE_8KB		__BF(4, 3, 6)
#define CP0_CPUID_ICACHE_SIZE_16KB		__BF(5, 3, 6)
#define CP0_CPUID_ICACHE_SIZE_32KB		__BF(6, 3, 6)
#define CP0_CPUID_ICACHE_SIZE_64KB		__BF(7, 3, 6)

#define CP0_CPUID_DCACHE_LINE_SELECT		__BS(2, 12)
#define CP0_CPUID_DCACHE_LINE_8BYTE		__BF(0, 2, 12)
#define CP0_CPUID_DCACHE_LINE_16BYTE		__BF(1, 2, 12)
#define CP0_CPUID_DCACHE_LINE_32BYTE		__BF(2, 2, 12)
#define CP0_CPUID_DCACHE_LINE_64BYTE		__BF(3, 2, 12)

#define CP0_CPUID_DCACHE_ASSOC_SELECT		__BS(3, 15)
#define CP0_CPUID_DCACHE_ASSOC_DMAP		__BF(0, 3, 15)
#define CP0_CPUID_DCACHE_ASSOC_2WAY		__BF(1, 3, 15)
#define CP0_CPUID_DCACHE_ASSOC_4WAY		__BF(2, 3, 15)
#define CP0_CPUID_DCACHE_ASSOC_8WAY		__BF(3, 3, 15)
#define CP0_CPUID_DCACHE_ASSOC_16WAY		__BF(4, 3, 15)
#define CP0_CPUID_DCACHE_ASSOC_32WAY		__BF(5, 3, 15)
#define CP0_CPUID_DCACHE_ASSOC_64WAY		__BF(6, 3, 15)
#define CP0_CPUID_DCACHE_ASSOC_128WAY		__BF(7, 3, 15)

#define CP0_CPUID_DCACHE_SIZE_SELECT		__BS(3, 18)
#define CP0_CPUID_DCACHE_SIZE_512B		__BF(0, 3, 18)
#define CP0_CPUID_DCACHE_SIZE_1KB		__BF(1, 3, 18)
#define CP0_CPUID_DCACHE_SIZE_2KB		__BF(2, 3, 18)
#define CP0_CPUID_DCACHE_SIZE_4KB		__BF(3, 3, 18)
#define CP0_CPUID_DCACHE_SIZE_8KB		__BF(4, 3, 18)
#define CP0_CPUID_DCACHE_SIZE_16KB		__BF(5, 3, 18)
#define CP0_CPUID_DCACHE_SIZE_32KB		__BF(6, 3, 18)
#define CP0_CPUID_DCACHE_SIZE_64KB		__BF(7, 3, 18)

#define CP0_CPUID_CACHE_SEPERATE		__BF(1, 1, 24)
#define CP0_CPUID_CACHE_LOCKDOWN		__BF(1, 1, 25)
#define CP0_CPUID_CACHE_WRITEBACK		__BF(1, 1, 26)
#define CP0_CPUID_CACHE_WRITETHROUGH		__BF(1, 1, 27)

#define CP0_TRAPSTAT_SELECT			__BS(4, 0)
#define CP0_TRAPSTAT_UNALIGN			__BF(1, 1, 4)

#endif /* __UNICORE64_ARCH_HWDEF_CP0_SYSCTRL_H__ */
