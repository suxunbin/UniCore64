#ifndef __UNICORE64_ARCH_HWDEF_CPU_H__
#define __UNICORE64_ARCH_HWDEF_CPU_H__

/**
 * DOC: HWDEF_CPU_H
 * This file defines the bit pattern for the processor status registers
 * and the processor flag registers.
 */
#include <arch/bitfield.h>

/**
 * DOC: HWDEF_CPU_H_ASR
 * Following ASR_* macros are defined:
 *
 * \\\\lt:programlisting\\\\gt:
 * -
 * ASR_MODE_MASK:	mode state mask
 * ASR_MODE_USER:	user state
 * ASR_MODE_PRIV:	privilege state
 * ASR_MODE_DEBUG:	debug state
 * -
 * ASR_T_BIT:		multi processors consistency enable bit
 * ASR_D_BIT:		debug mode enable bit
 * -
 * ASR_INTR_MASK:	interrupt mask
 * ASR_INTR_SMP:	interrupt between multi processors
 * ASR_INTR_LSU:	interrupt about LSU
 * ASR_INTR_ITM:	inner timer interrupt
 * ASR_INTR_OTM:	outer timer interrupt
 * ASR_INTR_DEV:	outer device interrupt
 * ASR_INTR_PFM:	performance monitor interrupt
 * -
 * \\\\lt:/programlisting\\\\gt:
 */
#define ASR_MODE_MASK		BFMASK(3, 0)
#define ASR_MODE_USER		BFIELD(1, 1, 0)
#define ASR_MODE_PRIV		BFIELD(1, 1, 1)
#define ASR_MODE_DEBUG		BFIELD(1, 1, 2)

#define ASR_T_BIT		BFIELD(1, 1, 3)
#define ASR_D_BIT		BFIELD(1, 1, 4)

#define ASR_INTR_MASK		BFMASK(6, 5)
#define ASR_INTR_SMP		BFIELD(1, 1, 5)
#define ASR_INTR_LSU		BFIELD(1, 1, 6)
#define ASR_INTR_ITM		BFIELD(1, 1, 7)
#define ASR_INTR_OTM		BFIELD(1, 1, 8)
#define ASR_INTR_DEV		BFIELD(1, 1, 9)
#define ASR_INTR_PFM		BFIELD(1, 1, 10)

/**
 * DOC: HWDEF_CPU_H_AFR
 * Following AFR_* macros are defined:
 *
 * \\\\lt:programlisting\\\\gt:
 * -
 * AFR_MASK:		AFR flag bit mask
 * AFR_V_BIT:		overflow flag bit
 * AFR_C_BIT:		carry flag bit
 * AFR_Z_BIT:		zero flag bit
 * AFR_S_BIT:		negative flag bit
 * -
 * \\\\lt:/programlisting\\\\gt:
 */
#define AFR_MASK		BFMASK(4, 0)
#define AFR_V_BIT		BFIELD(1, 1, 0)
#define AFR_C_BIT		BFIELD(1, 1, 1)
#define AFR_Z_BIT		BFIELD(1, 1, 2)
#define AFR_S_BIT		BFIELD(1, 1, 3)

#endif /* __UNICORE64_ARCH_HWDEF_CPU_H__ */
