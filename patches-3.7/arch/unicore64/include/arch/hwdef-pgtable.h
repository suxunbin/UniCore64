#ifndef __UNICORE64_ARCH_HWDEF_PGTABLE_H__
#define __UNICORE64_ARCH_HWDEF_PGTABLE_H__
/**
 * DOC: HWDEF_PGTABLE_H
 * This file make hardware address translation and page table definitions.
 */
#include <arch/bitfield.h>

/**
 * DOC: HWDEF_PGTABLE_H_ADDR_TRANSLATION
 * 3-level translation table walking: 9+9+9+12.
 * UC64_PGTBL_ENTRY_BITS, the logarithm of the size of pagetable entry space,
 * is the same for PGD/PMD/PTE, i.e., 8 bytes.
 */
#define UC64_PGTBL_ENTRY_BITS	(3)

#define UC64_PAGE_BITS		(12)
#define UC64_PAGE_SIZE		__BP(UC64_PAGE_BITS)
#define UC64_PAGE_MASK		__BM(UC64_PAGE_BITS, 0)
#define UC64_PAGE_SELECT	__BS(UC64_PAGE_BITS, 0)

#define UC64_PTE_BITS		(UC64_PAGE_BITS - UC64_PGTBL_ENTRY_BITS)
#define UC64_PTE_SIZE		__BP(UC64_PTE_BITS)
#define UC64_PTE_MASK		__BM(UC64_PTE_BITS, UC64_PAGE_BITS)

#define UC64_PMD_BITS		(UC64_PAGE_BITS - UC64_PGTBL_ENTRY_BITS)
#define UC64_PMD_SHIFT		(UC64_PAGE_BITS + UC64_PTE_BITS)
#define UC64_PMD_SIZE		__BP(UC64_PMD_SHIFT)
#define UC64_PMD_MASK		__BM(UC64_PMD_BITS, UC64_PMD_SHIFT)

#define UC64_SPAGE_BITS		(21)
#define UC64_SPAGE_SIZE		__BP(UC64_SPAGE_BITS)
#define UC64_SPAGE_MASK		__BM(UC64_SPAGE_BITS, 0)
#define UC64_SPAGE_SELECT	__BS(UC64_SPAGE_BITS, 0)

#define UC64_PGD_BITS		(UC64_PAGE_BITS - UC64_PGTBL_ENTRY_BITS)
#define UC64_PGD_SHIFT		(UC64_PMD_SHIFT + UC64_PGD_BITS)
#define UC64_PGD_SIZE		__BP(UC64_PGD_SHIFT)
#define UC64_PGD_MASK		__BM(UC64_PGD_BITS, UC64_PGD_SHIFT)

/**
 * DOC: HWDEF_PGTABLE_H_PGD
 * \\\\lt:programlisting\\\\gt:
 * PGD flag bits defined as below:
 * -
 * +---+---+---+---+---+---+---+---+---+---+---+---+
 * |   |   |   |   |   |   |   |   |   | E |   |   |
 * +---+---+---+---+---+---+---+---+---+---+---+---+
 * -
 * \\\\lt:/programlisting\\\\gt:
 * E: Exist bit
 */
#define UC64_PGD_EXIST		__BF(1, 1, 2)

/**
 * DOC: HWDEF_PGTABLE_H_PMD
 * \\\\lt:programlisting\\\\gt:
 * PMD flag bits defined as below:
 * -
 * +---+---+---+---+---+---+---+---+---+---+---+---+
 * | S |  MA   | G | R | W | X | M | A | E |U/S| PT|
 * +---+---+---+---+---+---+---+---+---+---+---+---+
 * -
 * S: Share bit
 * MA: Store type bit
 * G: Global bit
 * R: Read bit
 * W: Write bit
 * X: Execute bit
 * M: Modified bit
 * A: Accessed bit
 * E: Exist bit
 * U/S: User/Supervisor bit
 * PT: Page type bit
 * -
 * \\\\lt:/programlisting\\\\gt:
 */
#define UC64_PMD_SPAGE		__BF(1, 1, 0)
#define UC64_PMD_USER		__BF(1, 1, 1)
#define UC64_PMD_EXIST		__BF(1, 1, 2)
#define UC64_PMD_YOUNG		__BF(1, 1, 3)
#define UC64_PMD_DIRTY		__BF(1, 1, 4)
#define UC64_PMD_EXEC		__BF(1, 1, 5)
#define UC64_PMD_WRITE		__BF(1, 1, 6)
#define UC64_PMD_READ		__BF(1, 1, 7)
#define UC64_PMD_RWX		__BS(3, 5)
#define UC64_PMD_GLOBAL		__BF(1, 1, 8)
#define UC64_PMD_TYPE_SELECT	__BS(2, 9)
#define UC64_PMD_TYPE_IO	__BF(0, 2, 9)
#define UC64_PMD_TYPE_NOCACHE	__BF(1, 2, 9)
#define UC64_PMD_TYPE_CACHE	__BF(2, 2, 9)
#define UC64_PMD_SHARE		__BF(1, 1, 11)

/**
 * DOC: HWDEF_PGTABLE_H_PTE
 * \\\\lt:programlisting\\\\gt:
 * PTE flag bits defined as below:
 * -
 * +---+---+---+---+---+---+---+---+---+---+---+---+
 * | S |  MA   | G | R | W | X | M | A | E |U/S|Res|
 * +---+---+---+---+---+---+---+---+---+---+---+---+
 * -
 * S: Share bit
 * MA: Store type bit
 * G: Global bit
 * R: Read bit
 * W: Write bit
 * X: Execute bit
 * M: Modified bit
 * A: Accessed bit
 * E: Exist bit
 * U/S: User/Supervisor bit
 * Res: Reserved
 * -
 * \\\\lt:/programlisting\\\\gt:
 */
#define UC64_PTE_USER		__BF(1, 1, 1)
#define UC64_PTE_EXIST		__BF(1, 1, 2)
#define UC64_PTE_YOUNG		__BF(1, 1, 3)
#define UC64_PTE_DIRTY		__BF(1, 1, 4)
#define UC64_PTE_EXEC		__BF(1, 1, 5)
#define UC64_PTE_WRITE		__BF(1, 1, 6)
#define UC64_PTE_READ		__BF(1, 1, 7)
#define UC64_PTE_RWX		__BS(3, 5)
#define UC64_PTE_GLOBAL		__BF(1, 1, 8)
#define UC64_PTE_TYPE_SELECT	__BS(2, 9)
#define UC64_PTE_TYPE_IO	__BF(0, 2, 9)
#define UC64_PTE_TYPE_NOCACHE	__BF(1, 2, 9)
#define UC64_PTE_TYPE_CACHE	__BF(2, 2, 9)
#define UC64_PTE_SHARE		__BF(1, 1, 11)

#endif /* __UNICORE64_ARCH_HWDEF_PGTABLE_H__ */
