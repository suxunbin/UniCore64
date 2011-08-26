#ifndef __ASM_UNICORE64_PAGE_H__
#define __ASM_UNICORE64_PAGE_H__

#include <linux/const.h>

#define PAGE_OFFSET		_AC(0xfffffff800000000, UL)

/* PAGE_SHIFT determines the page size */
#define PAGE_SHIFT		(12)
#define PAGE_SIZE		(_AC(1, UL) << PAGE_SHIFT)
#define PAGE_MASK		(~(PAGE_SIZE-1))

#define clear_page(page)	memset((void *)(page), 0, PAGE_SIZE)
#define copy_page(to, from)	memcpy((void *)(to), (void *)(from), PAGE_SIZE)

#define clear_user_page(page, vaddr, pg)	clear_page(page)
#define copy_user_page(to, from, vaddr, pg)	copy_page(to, from)

#define __va(x)			((void *)((unsigned long)(x) + PAGE_OFFSET))
#define __pa(x)			((unsigned long)(x) - PAGE_OFFSET)

#define virt_to_page(kaddr)	pfn_to_page(__pa(kaddr) >> PAGE_SHIFT)
#define page_to_phys(page)	((dma_addr_t)page_to_pfn(page) << PAGE_SHIFT)

#define pfn_valid(pfn)		((pfn) < max_mapnr)

#define virt_addr_valid(kaddr)	pfn_valid(__pa(kaddr) >> PAGE_SHIFT)

#define VM_DATA_DEFAULT_FLAGS	(VM_READ | VM_WRITE | VM_EXEC | VM_MAYREAD | \
					VM_MAYWRITE | VM_MAYEXEC)

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

#include <asm-generic/getorder.h>
#include <asm-generic/memory_model.h>

#endif /* __ASM_UNICORE64_PAGE_H__ */
