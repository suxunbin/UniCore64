#ifndef __UNICORE64_ARCH_HWDEF_CPU_H__
#define __UNICORE64_ARCH_HWDEF_CPU_H__

/**
 * DOC: HWDEF_CPU_H
 * This file defines the bit pattern for the processor status registers
 * and the processor flag registers.
 */
#include <linux/stringify.h>
#include <arch/bitfield.h>

/**
 * DOC: HWDEF_CPU_H_ASR
 * Following ASR_* macros are defined:
 *
 * \\\\lt:programlisting\\\\gt:
 * -
 * ASR_MODE_SELECT:	mode state mask
 * ASR_MODE_USER:	user state
 * ASR_MODE_PRIV:	privilege state
 * ASR_MODE_DEBUG:	debug state
 * -
 * ASR_T_BIT:		multi processors consistency enable bit
 * ASR_D_BIT:		debug mode enable bit
 * -
 * ASR_INTR_SELECT:	interrupt mask
 * ASR_INTR_SMP:	interrupt between multi processors
 * ASR_INTR_LSU:	interrupt about LSU
 * ASR_INTR_ITM:	inner timer interrupt
 * ASR_INTR_OTM:	outer timer interrupt
 * ASR_INTR_DEV:	outer device interrupt
 * ASR_INTR_PFM:	performance monitor interrupt
 * -
 * \\\\lt:/programlisting\\\\gt:
 */
#define ASR_MODE_SELECT		__BS(3, 0)
#define ASR_MODE_USER		__BF(1, 1, 0)
#define ASR_MODE_PRIV		__BF(1, 1, 1)
#define ASR_MODE_DEBUG		__BF(1, 1, 2)

#define ASR_T_BIT		__BF(1, 1, 3)
#define ASR_D_BIT		__BF(1, 1, 4)

#define ASR_INTR_SELECT		__BS(6, 5)
#define ASR_INTR_SMP		__BF(1, 1, 5)
#define ASR_INTR_LSU		__BF(1, 1, 6)
#define ASR_INTR_ITM		__BF(1, 1, 7)
#define ASR_INTR_OTM		__BF(1, 1, 8)
#define ASR_INTR_DEV		__BF(1, 1, 9)
#define ASR_INTR_PFM		__BF(1, 1, 10)

/**
 * DOC: HWDEF_CPU_H_AFR
 * Following AFR_* macros are defined:
 *
 * \\\\lt:programlisting\\\\gt:
 * -
 * AFR_SELECT:		AFR flag bit mask
 * AFR_V_BIT:		overflow flag bit
 * AFR_C_BIT:		carry flag bit
 * AFR_Z_BIT:		zero flag bit
 * AFR_S_BIT:		negative flag bit
 * -
 * \\\\lt:/programlisting\\\\gt:
 */
#define AFR_SELECT		__BS(4, 0)
#define AFR_V_BIT		__BF(1, 1, 0)
#define AFR_C_BIT		__BF(1, 1, 1)
#define AFR_Z_BIT		__BF(1, 1, 2)
#define AFR_S_BIT		__BF(1, 1, 3)

/* To read asr, afr, bsr, and bsr */
#define __read_uc64(reg)					\
	({							\
		unsigned long __val;				\
		__asm__ __volatile__("dmov	%0, " __stringify(reg)	\
		    : "=r" (__val));				\
		__val;						\
	})

#define __write_uc64(reg_value, reg)				\
	({							\
		__asm__ __volatile__("dmov	" __stringify(reg) ", %0"\
		    : : "r" (reg_value));			\
	})

#endif /* __UNICORE64_ARCH_HWDEF_CPU_H__ */
