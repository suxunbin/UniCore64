#ifndef __UNICORE64_ARCH_PUV4_REGS_OST__
#define __UNICORE64_ARCH_PUV4_REGS_OST__

#include <arch/puv4-iomem.h>

/*
 * PUV4 Global OS Timer (OST) Registers
 *
 * OSMR0 OST Match Register 0
 * OSMR1 OST Match Register 1
 * OSMR2 OST Match Register 2
 * OSMR3 OST Match Register 3
 * OSCR OST Counter Register
 * OSSR OST Status Register
 * OIER OST Interrupt Enable Register
 */
#define OST_OSMR0	PUV4_IOREG(PUV4_OST_BASE + 0x00)
#define OST_OSMR1	PUV4_IOREG(PUV4_OST_BASE + 0x04)
#define OST_OSMR2	PUV4_IOREG(PUV4_OST_BASE + 0x08)
#define OST_OSMR3	PUV4_IOREG(PUV4_OST_BASE + 0x0c)
#define OST_OSCR	PUV4_IOREG(PUV4_OST_BASE + 0x10)
#define OST_OSSR	PUV4_IOREG(PUV4_OST_BASE + 0x14)
#define OST_OIER	PUV4_IOREG(PUV4_OST_BASE + 0x1c)

#define OST_OSSR_M0		__BF(1, 1, 0)
#define OST_OSSR_M1		__BF(1, 1, 1)
#define OST_OSSR_M2		__BF(1, 1, 2)
#define OST_OSSR_M3		__BF(1, 1, 3)

#define OST_OIER_E0		__BF(1, 1, 0)
#define OST_OIER_E1		__BF(1, 1, 1)
#define OST_OIER_E2		__BF(1, 1, 2)
#define OST_OIER_E3		__BF(1, 1, 3)

#endif /* __UNICORE64_ARCH_PUV4_REGS_OST__ */
