#ifndef __UNICORE64_ASM_PGTABLE_H__
#error "This file is included ONLY in asm/pgtable.h"
#endif

#include <asm/page.h>
#include <arch/hwdef-pgtable.h>

#define PAGE_KERNEL	__pgprot(UC64_PTE_RWX | UC64_PTE_DIRTY		\
		| UC64_PTE_EXIST | UC64_PTE_YOUNG | UC64_PTE_TYPE_CACHE \
		| UC64_PTE_SHARE)

/* FIXME: if READ is needed when WRITE or EXEC, otherwise, modify VM_flags */
#define arch_vm_get_page_prot(vm_flags) __pgprot(UC64_PTE_EXIST \
		| UC64_PTE_TYPE_CACHE | UC64_PTE_USER | UC64_PTE_SHARE)

/*
 * Mark the prot value as uncacheable.
 * NOTE: the same setting method for PTE and PMD.
 */
#define pgprot_noncached(prot)		\
	__pgprot((pgprot_val(prot) & ~UC64_PTE_TYPE_SELECT) | UC64_PTE_TYPE_NOCACHE)

#define __P000		__pgprot(0)
#define __P001		__pgprot(UC64_PTE_READ)
#define __P010		__pgprot(0)
#define __P011		__pgprot(UC64_PTE_READ)
#define __P100		__pgprot(UC64_PTE_EXEC)
#define __P101		__pgprot(UC64_PTE_EXEC | UC64_PTE_READ)
#define __P110		__pgprot(UC64_PTE_EXEC)
#define __P111		__pgprot(UC64_PTE_EXEC | UC64_PTE_READ)

#define __S000		__pgprot(0)
#define __S001		__pgprot(UC64_PTE_READ)
#define __S010		__pgprot(UC64_PTE_WRITE)
#define __S011		__pgprot(UC64_PTE_WRITE | UC64_PTE_READ)
#define __S100		__pgprot(UC64_PTE_EXEC)
#define __S101		__pgprot(UC64_PTE_EXEC | UC64_PTE_READ)
#define __S110		__pgprot(UC64_PTE_EXEC | UC64_PTE_WRITE)
#define __S111		__pgprot(UC64_PTE_RWX)
