#ifndef __UNICORE64_ARCH_REGS_INTC__
#define __UNICORE64_ARCH_REGS_INTC__

#include <arch/hwdef-puv3.h>

/*
 * PUV3 Interrupt Controller (INTC) Registers
 *
 * INTC Level Reg INTC_ICLR.
 * INTC Mask Reg INTC_ICMR.
 * INTC Pending Reg INTC_ICPR.
 * INTC IRQ Pending Reg INTC_ICIP.
 * INTC REAL Pending Reg INTC_ICFP.
 * INTC Control Reg INTC_ICCR.
 */
#define INTC_ICLR	(PUV3_INTC_BASE + 0x0000)
#define INTC_ICMR	(PUV3_INTC_BASE + 0x0004)
#define INTC_ICPR	(PUV3_INTC_BASE + 0x0008)
#define INTC_ICIP	(PUV3_INTC_BASE + 0x000C)
#define INTC_ICFP	(PUV3_INTC_BASE + 0x0010)
#define INTC_ICCR	(PUV3_INTC_BASE + 0x0014)

#endif /* __UNICORE64_ARCH_REGS_INTC__ */
