#ifndef __UNICORE64_ARCH_PUV3_GPIO__
#define __UNICORE64_ARCH_PUV3_GPIO__

#include <arch/puv3-iomem.h>

/*
 * PUV3 General-Purpose Input/Output (GPIO) Registers
 *
 * Voltage Status Reg GPIO_GPLR.
 * Pin Direction Reg GPIO_GPDR.
 * Output Pin Set Reg GPIO_GPSR.
 * Output Pin Clear Reg GPIO_GPCR.
 * Raise Edge Detect Reg GPIO_GRER.
 * Fall Edge Detect Reg GPIO_GFER.
 * Edge Status Reg GPIO_GEDR.
 * Sepcial Voltage Detect Reg GPIO_GPIR.
 */
#define GPIO_GPLR		PUV3_IOREG(PUV3_GPIO_BASE + 0x0000)
#define GPIO_GPDR		PUV3_IOREG(PUV3_GPIO_BASE + 0x0004)
#define GPIO_GPSR		PUV3_IOREG(PUV3_GPIO_BASE + 0x0008)
#define GPIO_GPCR		PUV3_IOREG(PUV3_GPIO_BASE + 0x000C)
#define GPIO_GRER		PUV3_IOREG(PUV3_GPIO_BASE + 0x0010)
#define GPIO_GFER		PUV3_IOREG(PUV3_GPIO_BASE + 0x0014)
#define GPIO_GEDR		PUV3_IOREG(PUV3_GPIO_BASE + 0x0018)
#define GPIO_GPIR		PUV3_IOREG(PUV3_GPIO_BASE + 0x0020)

#define GPIO_MIN		(0)
#define GPIO_MAX		(27)

#define GPIO_GPIO(Nb)		__BF(1, (Nb))	/* GPIO [0..27] */

#endif /* __UNICORE64_ARCH_PUV3_GPIO__ */
