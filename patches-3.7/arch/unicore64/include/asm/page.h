#ifndef __ASM_UNICORE64_PAGE_H__
#define __ASM_UNICORE64_PAGE_H__

#include <linux/const.h>

#define PAGE_OFFSET		_AC(0xfffffff800000000, UL)

/* PAGE_SHIFT determines the page size */
#define PAGE_SHIFT		(12)
#define PAGE_SIZE		(_AC(1, UL) << PAGE_SHIFT)
#define PAGE_MASK		(~(PAGE_SIZE-1))

#define STRICT_MM_TYPECHECKS

#ifdef STRICT_MM_TYPECHECKS
/* These are used to make use of C type-checking.. */
typedef struct { u64 pte; } pte_t;
typedef struct { u64 pmd; } pmd_t;
typedef struct { u64 pgd; } pgd_t;
typedef struct { u64 pgprot; } pgprot_t;

#define pte_val(x)	((x).pte)
#define pmd_val(x)	((x).pmd)
#define pgd_val(x)	((x).pgd)
#define pgprot_val(x)	((x).pgprot)

#define __pte(x)	((pte_t) { (x) })
#define __pmd(x)	((pmd_t) { (x) })
#define __pgd(x)	((pgd_t) { (x) })
#define __pgprot(x)	((pgprot_t) { (x) })

#else /* STRICT_MM_TYPECHECKS */
/* .. while these make it easier on the compiler */
typedef u64 pte_t;
typedef u64 pmd_t;
typedef u64 pgd_t;
typedef u64 pgprot_t;

#define pte_val(x)	(x)
#define pmd_val(x)	(x)
#define pgd_val(x)	(x)
#define pgprot_val(x)	(x)

#define __pte(x)	(x)
#define __pmd(x)	(x)
#define __pgd(x)	(x)
#define __pgprot(x)	(x)

#endif /* STRICT_MM_TYPECHECKS */

typedef struct page *pgtable_t;

#define __va(x)			((void *)((unsigned long)(x) + PAGE_OFFSET))
#define __pa(x)			((unsigned long)(x) - PAGE_OFFSET)

#define virt_to_page(kaddr)	pfn_to_page(__pa(kaddr) >> PAGE_SHIFT)

#include <asm-generic/getorder.h>
#include <asm-generic/memory_model.h>

#endif /* __ASM_UNICORE64_PAGE_H__ */
