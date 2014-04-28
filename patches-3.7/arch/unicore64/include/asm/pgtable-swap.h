#ifndef __UNICORE64_ASM_PGTABLE_H__
#error "This file is included ONLY in asm/pgtable.h"
#endif

#define UC64_PTE_FILE			UC64_PTE_YOUNG /* only when !PRESENT */
#define PTE_FILE_MAX_BITS		61 /* FIXME */

#define __SWP_TYPE_SHIFT		5
#define __SWP_TYPE_BITS			7
#define __SWP_OFFSET_SHIFT	(__SWP_TYPE_BITS + __SWP_TYPE_SHIFT)
#define __SWP_TYPE_MASK		((1 << __SWP_TYPE_BITS) - 1)
#define __swp_type(x)		(((x).val >> __SWP_TYPE_SHIFT)	\
				& __SWP_TYPE_MASK)
#define __swp_offset(x)		((x).val >> __SWP_OFFSET_SHIFT)
#define __swp_entry(type, offset)   ((swp_entry_t) {  \
				    ((type) << __SWP_TYPE_SHIFT) | \
				    ((offset) << __SWP_OFFSET_SHIFT) })
#define __pte_to_swp_entry(pte)		((swp_entry_t) { pte_val(pte) })
#define __swp_entry_to_pte(swp)		((pte_t) { (swp).val })

#define pte_file(pte)			(pte_val(pte) & UC64_PTE_FILE)
#define pte_to_pgoff(x)			({BUG(); 0; })
#define pgoff_to_pte(x)			__pte({BUG(); 0; })
