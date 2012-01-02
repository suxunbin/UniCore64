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
#define UC64_VM_USER_START		HEX64(00000000, 00000000)
#define UC64_VM_USER_END		HEX64(0000001f, ffffffff)
/* virtual address of KERNEL space */
#define UC64_VM_KERNEL_START		HEX64(ffffffe0, 00000000)
#define UC64_VM_KERNEL_END		HEX64(ffffffff, ffffffff)

/* virtual address of direct mapping space */
#define UC64_VM_DMAP_START		UC64_VM_KERNEL_START
#define UC64_VM_DMAP_END		HEX64(ffffffef, ffffffff)

/* FIXME */
#define UC64_VM_VMALLOC_START		HEX64(00000001, 00000000)
#define UC64_VM_VMALLOC_END		HEX64(00000002, 00000000)

/**
 * DOC: HWDEF_MEMORY_H_PM
 * We have 36-bit pm address which means 64GB physical space
 * as below:
 */
#define UC64_PM_START			HEX64(00000000, 00000000)
#define UC64_PM_END			HEX64(0000000f, ffffffff)

#define UC64_PM2VM(paddr)		(UC64_VM_KERNEL_START + (paddr))

/*
 * The byte offset of the kernel image in RAM from the start of RAM.
 * We must make sure that UC64_VM_KIMAGE_START is correctly set.
 * Currently, we expect the least significant 24 bits to be 0x408000.
 */
#define UC64_PM_KIMAGE_START		HEX64(00000000, 00408000)
#define UC64_VM_KIMAGE_START		UC64_PM2VM(UC64_PM_KIMAGE_START)

/*
 * The byte offset of the unicore64.dtb in RAM from the start of RAM.
 * We must make sure that UC64_VM_DTB_START is correctly set.
 * Currently, we expect the least significant 24 bits to be 0x401000.
 */
#define UC64_PM_DTB_START		HEX64(00000000, 00401000)
#define UC64_VM_DTB_START		UC64_PM2VM(UC64_PM_DTB_START)

/*
 * Physical and virtual address of the initial page table.
 * We place the page tables 4K below UC64_VM_KIMAGE_START.
 */
#define UC64_PM_PGTABLE_PGD		(UC64_PM_KIMAGE_START - UC64_PAGE_SIZE)
#define UC64_VM_PGTABLE_PGD		UC64_PM2VM(UC64_PM_PGTABLE_PGD)

/*
 * Physical address of the direct map pmd.
 */
#define UC64_PM_PGTABLE_DMAP_PMD	(UC64_PM_PGTABLE_PGD - UC64_PAGE_SIZE)

/* The byte offset of zImage in RAM from the start of RAM. */
#define UC64_PM_ZIMAGE_START		HEX64(00000000, 03000000)

/* The address of stack and heap. */
#define UC64_PM_ZIMAGE_SP		HEX64(00000000, 03e00000)
#define UC64_PM_ZIMAGE_HEAP		HEX64(00000000, 04000000)

#endif /* __UNICORE64_ARCH_HWDEF_MEMORY_H__ */
