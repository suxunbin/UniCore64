#ifndef __UNICORE64_ARCH_PUV4_IOMEM_H__
#define __UNICORE64_ARCH_PUV4_IOMEM_H__

#include <linux/types.h>
#include <arch/hwdef-memory.h>

#ifndef __ASSEMBLY__
#define PUV4_IOMEM(x)			(resource_size_t)(UC64_VM_IO_START + (x))
#define PUV4_IOREG(x)			(void __iomem *)(x)
#else
#define PUV4_IOMEM(x)			(UC64_VM_IO_START + (x))
#define PUV4_IOREG(x)			(x)
#endif

/* Assume the region for every ip in puv4 having 4K iomem */
#define PUV4_IOMEM_REGION		__BS(12, 0)

/*
 * PUV4 System Bus Addresses (PCI): 0x80000000 - 0xBFFFFFFF (1GB)
 * 0x80000000 - 0x8000000B 12B    PCI Configuration regs
 * 0x80010000 - 0x80010250 592B   PCI Bridge Base
 * 0x80030000 - 0x8003FFFF 64KB   PCI Legacy IO
 * 0x90000000 - 0x97FFFFFF 128MB  PCI AHB-PCI MEM-mapping
 * 0x98000000 - 0x9FFFFFFF 128MB  PCI PCI-AHB MEM-mapping
 */
#define PUV4_PCI_BASE			PUV4_IOMEM(0x00000000)
#define PUV4_PCICFG_BASE		(PUV4_PCI_BASE + 0x0)
#define PUV4_PCIBRI_BASE		(PUV4_PCI_BASE + 0x00010000)
#define PUV4_PCILIO_BASE		(PUV4_PCI_BASE + 0x00030000)
#define PUV4_PCIMEM_BASE		(PUV4_PCI_BASE + 0x10000000)
#define PUV4_PCIAHB_BASE		(PUV4_PCI_BASE + 0x18000000)

/*
 * PUV4 System Bus Addresses (AHB): 0xC0000000 - 0xEDFFFFFF (640MB)
 */
#define PUV4_AHB_BASE			PUV4_IOMEM(0x40000000)

/* AHB-0 is DDR2 SDRAM */
/* AHB-1 is PCI Space */
#define PUV4_ARBITER_BASE		(PUV4_AHB_BASE + 0x000000) /* AHB-2 */
#define PUV4_DDR2CTRL_BASE		(PUV4_AHB_BASE + 0x100000) /* AHB-3 */
#define PUV4_DMAC_BASE			(PUV4_AHB_BASE + 0x200000) /* AHB-4 */
#define PUV4_UMAL_BASE			(PUV4_AHB_BASE + 0x300000) /* AHB-5 */
#define PUV4_USB_BASE			(PUV4_AHB_BASE + 0x400000) /* AHB-6 */
#define PUV4_SATA_BASE			(PUV4_AHB_BASE + 0x500000) /* AHB-7 */
#define PUV4_SMC_BASE			(PUV4_AHB_BASE + 0x600000) /* AHB-8 */
/* AHB-9 is for APB bridge */
#define PUV4_MME_BASE			(PUV4_AHB_BASE + 0x700000) /* AHB-10 */
#define PUV4_UNIGFX_BASE		(PUV4_AHB_BASE + 0x800000) /* AHB-11 */
#define PUV4_NAND_BASE			(PUV4_AHB_BASE + 0x900000) /* AHB-12 */
#define PUV4_H264D_BASE			(PUV4_AHB_BASE + 0xA00000) /* AHB-13 */
#define PUV4_H264E_BASE			(PUV4_AHB_BASE + 0xB00000) /* AHB-14 */
#define PUV4_UNIPATAS_BASE		(PUV4_AHB_BASE + 0xd00000) /* AHB-15 */
#define PUV4_UNIPATAE_BASE		(PUV4_AHB_BASE + 0xd01000) /* AHB-16 */

/*
 * PUV4 Peripheral Bus Addresses (APB): 0xEE000000 - 0xEFFFFFFF (128MB)
 */
#define PUV4_APB_BASE			PUV4_IOMEM(0x6E000000)

#define PUV4_UART0_BASE			(PUV4_APB_BASE + 0x000000) /* APB-0 */
#define PUV4_UART1_BASE			(PUV4_APB_BASE + 0x100000) /* APB-1 */
#define PUV4_I2C_BASE			(PUV4_APB_BASE + 0x200000) /* APB-2 */
#define PUV4_SPI_BASE			(PUV4_APB_BASE + 0x300000) /* APB-3 */
#define PUV4_AC97_BASE			(PUV4_APB_BASE + 0x400000) /* APB-4 */
#define PUV4_GPIO_BASE			(PUV4_APB_BASE + 0x500000) /* APB-5 */
#define PUV4_INTC_BASE			(PUV4_APB_BASE + 0x600000) /* APB-6 */
#define PUV4_RTC_BASE			(PUV4_APB_BASE + 0x700000) /* APB-7 */
#define PUV4_OST_BASE			(PUV4_APB_BASE + 0x800000) /* APB-8 */
#define PUV4_RESETC_BASE		(PUV4_APB_BASE + 0x900000) /* APB-9 */
#define PUV4_PM_BASE			(PUV4_APB_BASE + 0xA00000) /* APB-10 */
#define PUV4_SDC_BASE			(PUV4_APB_BASE + 0xC00000) /* APB-12 */

/* FIXME: For FPGA board ONLY */
#define PUV4_PS2_BASE			(PUV4_APB_BASE + 0x1100000)
#include <arch/puv4-regs-ps2.h>

/* FIXME:
 * PKUNITY Memory Map Addresses: 0x03000000 - 0x03FFFFFF (16MB)
 */
#define PKUNITY_DE2_MMAP_BASE	        0x03800000 \
/* 0x03800000 - 0x04000000 8MB */
#define PKUNITY_DE2_MMAP_SIZE		0x00800000 /* 8MB */
#define PKUNITY_VPU_MMAP_BASE	        0x0C000000 \
/* 0x0C000000 - 0x15FFFFFF 160MB */
#define PKUNITY_VPU_MMAP_SIZE		0x0A000000 /* 160MB */
#define PKUNITY_UNIGFX2_BASE		(PUV4_AHB_BASE + 0xC00000) /* FIXME */
#include <arch/puv4-regs-unigfx2.h>

#endif  /* __UNICORE64_ARCH_PUV4_IOMEM_H__ */
