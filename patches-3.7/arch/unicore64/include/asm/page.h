#ifndef __UNICORE64_ASM_PAGE_H__
#define __UNICORE64_ASM_PAGE_H__

#include <arch/hwdef-memory.h>
#include <arch/hwdef-pgtable.h>

/* Virtual start address of the first bank of RAM */
#define PAGE_OFFSET		UC64_VM_DMAP_START

/* PAGE_SHIFT determines the page size */
#define PAGE_SHIFT		UC64_PAGE_BITS
#define PAGE_SIZE		UC64_PAGE_SIZE
#define PAGE_MASK		__BM(PAGE_SHIFT, 0)

#ifndef __ASSEMBLY__

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

typedef struct page *pgtable_t;

typedef struct { unsigned long pte; } pte_t;
typedef struct { unsigned long pmd; } pmd_t;
typedef struct { unsigned long pgd; } pgd_t;
typedef struct { unsigned long pgprot; } pgprot_t;

#define pte_val(x)	((x).pte)
#define pmd_val(x)	((x).pmd)
#define pgd_val(x)	((x).pgd)
#define pgprot_val(x)	((x).pgprot)

#define __pte(x)	((pte_t) { (x) })
#define __pmd(x)	((pmd_t) { (x) })
#define __pgd(x)	((pgd_t) { (x) })
#define __pgprot(x)	((pgprot_t) { (x) })

#endif /* !__ASSEMBLY__ */

#include <asm-generic/getorder.h>
#include <asm-generic/memory_model.h>

#endif /* __UNICORE64_ASM_PAGE_H__ */
