#ifndef __UNICORE64_ARCH_HWDEF_MEMORY_H__
#define __UNICORE64_ARCH_HWDEF_MEMORY_H__

/**
 * DOC: HWDEF_MEMORY_H
 * This file defines memory layout for VM & PM.
 */
#include <arch/bitfield.h>
#include <arch/hwdef-pgtable.h>

/**
 * DOC: HWDEF_MEMORY_H_VM
 * We have 39-bit vm address which means 512GB virtual space.
 * Use the [38:37] bits(the higher bits are extended the same as the
 * 38th bit) to divide it in 4 parts as below:
 *
 * \\\\lt:programlisting\\\\gt:
 * -
 * -[38:37]bits                         Address Range           Size
 * -            +---------------+
 * -            |               |      0xffffffff_ffffffff
 * -    11b     | Kernel space  |     |                         128GB
 * -            |               |      0xffffffe0_00000000
 * -            +---------------+
 * -            |               |      0xffffffdf_ffffffff
 * -    10b     |   Reserved    |     |                         128GB
 * -            |               |      0xffffffc0_00000000
 * -            +---------------+
 * -            ~     Hole      ~      For sign-expanion
 * -            +---------------+
 * -            |               |      0x0000003f_ffffffff
 * -    01b     |   Reserved    |     |                         128GB
 * -            |               |      0x00000020_00000000
 * -            +---------------+
 * -            |               |      0x0000001f_ffffffff
 * -    00b     |  User space   |     |                         128GB
 * -            |               |      0x00000000_00000000
 * -            +---------------+
 * -
 * \\\\lt:/programlisting\\\\gt:
 *
 * In the Kernel space, the last 64GB(physical space is 64G) space
 * is Direct Mapping space.
 */

/* virtual address of USER space */
#define UC64_VM_USER_START		__BC(00000000, 00000000)
#define UC64_VM_USER_END		__BC(00000020, 00000000)
/* virtual address of KERNEL space, in which DMAP means Direct MAPping */
#define UC64_VM_KERNEL_START		__BC(ffffffe0, 00000000)
#define UC64_VM_DMAP_START		__BC(fffffff0, 00000000)
#define UC64_VM_IO_START		__BC(ffffffff, 80000000)

/* FIXME */
#define UC64_VM_VMALLOC_START		__BC(00000001, 00000000)
#define UC64_VM_VMALLOC_END		__BC(00000002, 00000000)

/**
 * DOC: HWDEF_MEMORY_H_PM
 * We have 36-bit pm address which means 64GB physical space
 * as below:
 *
 * ZIMAGE_START: The byte offset of zImage in RAM from the start of RAM
 * ZIMAGE_STACKTOP: sp value for uncompressing period
 * ZIMAGE_HEAP_END: malloc space above stack
 *
 */
#define UC64_PM_START			__BC(00000000, 00000000)
#define UC64_PM_END			__BC(00000010, 00000000)

#define UC64_PM_ZIMAGE_START		__BC(00000000, 03000000)
#define UC64_PM_ZIMAGE_STACKTOP		__BC(00000000, 03800000)
#define UC64_PM_ZIMAGE_HEAP_END		__BC(00000000, 03f00000)

/*
 * Address space: 00400000 - 00408000
 *
 * KIMAGE_START:
 * The byte offset of the kernel image in RAM from the start of RAM.
 * We must make sure that UC64_VM_KIMAGE_START is correctly set.
 * Currently, we expect the least significant 24 bits to be 0x408000.
 *
 * DTB_START:
 * The byte offset of the unicore64.dtb in RAM from the start of RAM.
 * We must make sure that UC64_VM_DTB_START is correctly set.
 * Currently, we expect the least significant 24 bits to be 0x401000.
 *
 * ZEROPAGE:
 * This page is reserved for zero page.
 *
 * PGTABLE_PGD:
 * Physical and virtual address of the initial page table.
 * We place the page tables 4K below UC64_VM_KIMAGE_START.
 *
 * PGTABLE_PMD_*:
 * Physical address of the direct map pmd.
 */
#define UC64_PM_KIMAGE_START		__BC(00000000, 00408000)
#define UC64_PM_DTB_START		__BC(00000000, 00400000)
#define UC64_PM_ZEROPAGE		__BC(00000000, 00403000)
#define UC64_PM_PGTABLE_PGD		__BC(00000000, 00404000)
#define UC64_PM_PGTABLE_PUD_DM00	__BC(00000000, 00405000)
#define UC64_PM_PGTABLE_PUD_IO00	__BC(00000000, 00406000)
#define UC64_PM_PGTABLE_PUD_IO01	__BC(00000000, 00407000)
#define UC64_PM_NONCACHED_START		__BC(00000000, 03000000)
#define UC64_PM_FRAME_START		__BC(00000000, 03000000)
#define UC64_PM_DMAOVERFLOW_START	__BC(00000000, 03e00000)
#define UC64_PM_DMA_START		__BC(00000000, 04000000)
#define UC64_PM_NONCACHED_END		__BC(00000000, 08000000)

#define UC64_PM2VM(paddr)		(UC64_VM_DMAP_START + (paddr))

#define UC64_VM_KIMAGE_START		UC64_PM2VM(UC64_PM_KIMAGE_START)
#define UC64_VM_DTB_START		UC64_PM2VM(UC64_PM_DTB_START)
#define UC64_VM_ZEROPAGE		UC64_PM2VM(UC64_PM_ZEROPAGE)
#define UC64_VM_PGTABLE_PGD		UC64_PM2VM(UC64_PM_PGTABLE_PGD)
#define UC64_VM_NONCACHED_START		UC64_PM2VM(UC64_PM_NONCACHED_START)
#define UC64_VM_FRAME_START		UC64_PM2VM(UC64_PM_FRAME_START)
#define UC64_VM_DMAOVERFLOW_START	UC64_PM2VM(UC64_PM_DMAOVERFLOW_START)
#define UC64_VM_DMA_START		UC64_PM2VM(UC64_PM_DMA_START)
#define UC64_VM_NONCACHED_END		UC64_PM2VM(UC64_PM_NONCACHED_END)

#endif /* __UNICORE64_ARCH_HWDEF_MEMORY_H__ */
