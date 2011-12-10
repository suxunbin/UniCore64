#ifndef __UNICORE64_ARCH_HWDEF_PGTABLE_H__
#define __UNICORE64_ARCH_HWDEF_PGTABLE_H__

#include <arch/bitfield.h>

/* Hardware address translation and page table definitions. */
/*
 * 3-level translation table walking: 9+9+9+12
 * UC64_PGTBL_ENTRY_BITS: the logarithm of the size of pagetable entry space,
 * which is the same for PGD/PMD/PTE, i.e., 8 bytes.
 */
#define UC64_PGTBL_ENTRY_BITS	(3)

#define UC64_PAGE_BITS		(12)
#define UC64_PAGE_SIZE		BFSIZE(UC64_PAGE_BITS)
#define UC64_PAGE_MASK		BFMASK(UC64_PAGE_BITS, 0)

#define UC64_PTE_BITS		(UC64_PAGE_BITS - UC64_PGTBL_ENTRY_BITS)
#define UC64_PTE_SIZE		BFSIZE(UC64_PTE_BITS)
#define UC64_PTE_MASK		BFMASK(UC64_PTE_BITS, UC64_PAGE_BITS)

#define UC64_PMD_BITS		(UC64_PAGE_BITS - UC64_PGTBL_ENTRY_BITS)
#define UC64_PMD_SHIFT		(UC64_PAGE_BITS + UC64_PTE_BITS)
#define UC64_PMD_SIZE		BFSIZE(UC64_PMD_SHIFT)
#define UC64_PMD_MASK		BFMASK(UC64_PMD_BITS, UC64_PMD_SHIFT)

#define UC64_PGD_BITS		(UC64_PAGE_BITS - UC64_PGTBL_ENTRY_BITS)
#define UC64_PGD_SHIFT		(UC64_PMD_SHIFT + UC64_PGD_BITS)
#define UC64_PGD_SIZE		BFSIZE(UC64_PGD_SHIFT)
#define UC64_PGD_MASK		BFMASK(UC64_PGD_BITS, UC64_PGD_SHIFT)

/* Level 1 descriptor (PGD) */
#define PGD_EXIST		BFIELD(1, 1, 2)

/* Level 2 descriptor (PMD) */
#define PMD_SUPER		BFIELD(1, 1, 0)
#define PMD_USER		BFIELD(1, 1, 1)
#define PMD_EXIST		BFIELD(1, 1, 2)
#define PMD_YOUNG		BFIELD(1, 1, 3)
#define PMD_DIRTY		BFIELD(1, 1, 4)
#define PMD_EXEC		BFIELD(1, 1, 5)
#define PMD_WRITE		BFIELD(1, 1, 6)
#define PMD_READ		BFIELD(1, 1, 7)
#define PMD_RWX			(PMD_READ | PMD_WRITE | PMD_EXEC)
#define PMD_GLOBAL		BFIELD(1, 1, 8)
#define PMD_TYPE_MASK		BFMASK(2, 9)
#define PMD_TYPE_IO		BFIELD(0, 2, 9)
#define PMD_TYPE_NOCACHE	BFIELD(1, 2, 9)
#define PMD_TYPE_CACHE		BFIELD(2, 2, 9)
#define PMD_SHARE		BFIELD(1, 1, 11)

/* Level 3 descriptor (PTE) */
#define PTE_USER		BFIELD(1, 1, 1)
#define PTE_EXIST		BFIELD(1, 1, 2)
#define PTE_YOUNG		BFIELD(1, 1, 3)
#define PTE_DIRTY		BFIELD(1, 1, 4)
#define PTE_EXEC		BFIELD(1, 1, 5)
#define PTE_WRITE		BFIELD(1, 1, 6)
#define PTE_READ		BFIELD(1, 1, 7)
#define PTE_RWX			(PTE_READ | PTE_WRITE | PTE_EXEC)
#define PTE_GLOBAL		BFIELD(1, 1, 8)
#define PTE_TYPE_MASK		BFMASK(2, 9)
#define PTE_TYPE_IO		BFIELD(0, 2, 9)
#define PTE_TYPE_NOCACHE	BFIELD(1, 2, 9)
#define PTE_TYPE_CACHE		BFIELD(2, 2, 9)
#define PTE_SHARE		BFIELD(1, 1, 11)

#endif /* __UNICORE64_ARCH_HWDEF_PGTABLE_H__ */
