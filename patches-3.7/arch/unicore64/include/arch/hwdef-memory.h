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
 * Use the 38:37 bits(the higher bits are extended the same as the
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
 * In the Kernel space, the first 64GB(physical space is 64G) space
 * is Direct Mapping space.
 */

/* virtual address of USER space */
#define UC64_VM_USER_START		__BC(00000000, 00000000)
#define UC64_VM_USER_END		__BC(0000001f, ffffffff)
/* virtual address of KERNEL space */
#define UC64_VM_KERNEL_START		__BC(ffffffe0, 00000000)
#define UC64_VM_KERNEL_END		__BC(ffffffff, ffffffff)

/* virtual address of direct mapping space */
#define UC64_VM_DMAP_START		UC64_VM_KERNEL_START
#define UC64_VM_DMAP_END		__BC(ffffffef, ffffffff)

#define UC64_VM_IO_START		__BC(ffffffef, 80000000)
#define UC64_VM_IO_END			UC64_VM_DMAP_END

/* FIXME */
#define UC64_VM_VMALLOC_START		__BC(00000001, 00000000)
#define UC64_VM_VMALLOC_END		__BC(00000002, 00000000)

/**
 * DOC: HWDEF_MEMORY_H_PM
 * We have 36-bit pm address which means 64GB physical space
 * as below:
 *
 * ZIMAGE_START: The byte offset of zImage in RAM from the start of RAM.
 * ZIMAGE_SP & ZIMAGE_HEAP: The address of stack and heap.
 *
 */
#define UC64_PM_START			__BC(00000000, 00000000)
#define UC64_PM_END			__BC(0000000f, ffffffff)

#define UC64_PM_ZIMAGE_START		__BC(00000000, 03000000)
#define UC64_PM_ZIMAGE_SP		__BC(00000000, 03e00000)
#define UC64_PM_ZIMAGE_HEAP		__BC(00000000, 04000000)

/*
 * Address space: 00400000 - 00408000
 *
 * KIMAGE_START:
 * The byte offset of the kernel image in RAM from the start of RAM.
 * We must make sure that UC64_VM_KIMAGE_START is correctly set.
 * Currently, we expect the least significant 24 bits to be 0x408000.
 *
 * PGTABLE_PGD:
 * Physical and virtual address of the initial page table.
 * We place the page tables 4K below UC64_VM_KIMAGE_START.
 *
 * PGTABLE_DMAP_PMD:
 * Physical address of the direct map pmd.
 *
 * ZEROPAGE:
 * This page is reserved for zero page.
 *
 * DTB_START:
 * The byte offset of the unicore64.dtb in RAM from the start of RAM.
 * We must make sure that UC64_VM_DTB_START is correctly set.
 * Currently, we expect the least significant 24 bits to be 0x401000.
 */
#define UC64_PM_KIMAGE_START		__BC(00000000, 00408000)
#define UC64_PM_PGTABLE_PGD		__BC(00000000, 00407000)
#define UC64_PM_PGTABLE_DMAP_PMD	__BC(00000000, 00406000)
#define UC64_PM_ZEROPAGE		__BC(00000000, 00404000)
#define UC64_PM_DTB_START		__BC(00000000, 00401000)

#define UC64_PM2VM(paddr)		(UC64_VM_KERNEL_START + (paddr))

#define UC64_VM_KIMAGE_START		UC64_PM2VM(UC64_PM_KIMAGE_START)
#define UC64_VM_PGTABLE_PGD		UC64_PM2VM(UC64_PM_PGTABLE_PGD)
#define UC64_VM_ZEROPAGE		UC64_PM2VM(UC64_PM_ZEROPAGE)
#define UC64_VM_DTB_START		UC64_PM2VM(UC64_PM_DTB_START)

#define UC64_IO_SOC_START		__BC(0000000f, 80000000)
#define UC64_IO_SOC_END			__BC(0000000f, ffffffff)

#define UC64_IO_OCD_START		__BC(0000000f, ff400000)
#define UC64_IO_OCD_END			__BC(0000000f, ff5fffff)

#define UC64_IO2VM(ioaddr)		(UC64_VM_IO_START + (ioaddr))

#define UC64_VM_IO_SOC_START		UC64_IO2VM(UC64_IO_SOC_START)
#define UC64_VM_IO_SOC_END		UC64_IO2VM(UC64_IO_SOC_END)

#endif /* __UNICORE64_ARCH_HWDEF_MEMORY_H__ */
