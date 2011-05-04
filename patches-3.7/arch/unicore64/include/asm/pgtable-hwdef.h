#ifndef __ASM_UNICORE64_PGTABLE_HWDEF_H__
#define __ASM_UNICORE64_PGTABLE_HWDEF_H__

/* Hardware page table definitions. */

/* Level 1 descriptor (PGD) */
#define UC64_L1_EXIST		(1 << 2)

/* Level 2 descriptor (PMD) */
#define UC64_L2_EXIST		(1 << 2)

/* Level 3 descriptor (PTE) */
#define UC64_L3_EXIST		(1 << 2)
#define UC64_L3_YOUNG		(1 << 3)
#define UC64_L3_DIRTY		(1 << 4)
#define UC64_L3_EXEC		(1 << 5)
#define UC64_L3_WRITE		(1 << 6)
#define UC64_L3_READ		(1 << 7)

#endif /* __ASM_UNICORE64_PGTABLE_HWDEF_H__ */
