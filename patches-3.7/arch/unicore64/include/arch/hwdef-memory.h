#ifndef __UNICORE64_ARCH_HWDEF_MEMORY_H__
#define __UNICORE64_ARCH_HWDEF_MEMORY_H__

#include <arch/bitfield.h>

/**
 * DOC: HWDEF_MEMORY_H
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
 * In the Kernel space, the first 64GB(physical space is 64G) space
 * is Direct Mapping space.
 * \\\\lt:/programlisting\\\\gt:
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

/*
 * We have 36-bit pm address which means 64GB physical space
 * as below:
 */
#define UC64_PM_START			HEX64(00000000, 00000000)
#define UC64_PM_END			HEX64(0000000f, ffffffff)

/* The byte offset of the kernel image in RAM from the start of RAM. */
#define UC64_PM_KIMAGE_START		HEX64(00000000, 00408000)

#endif /* __UNICORE64_ARCH_HWDEF_MEMORY_H__ */
