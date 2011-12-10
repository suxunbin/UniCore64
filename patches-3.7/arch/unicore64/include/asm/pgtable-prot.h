#ifndef __UNICORE64_ASM_PGTABLE_H__
#error "This file is included ONLY in asm/pgtable.h"
#endif

#include <asm/page.h>
#include <arch/hwdef-pgtable.h>

#define PAGE_KERNEL	__pgprot(PTE_RWX | PTE_DIRTY | PTE_EXIST | PTE_YOUNG \
					| PTE_TYPE_CACHE)

/* FIXME: if READ is needed when WRITE or EXEC, otherwise, modify VM_flags */
#define arch_vm_get_page_prot(vm_flags)	__pgprot(PTE_EXIST | PTE_TYPE_CACHE)

#define __P000		__pgprot(0)
#define __P001		__pgprot(PTE_READ)
#define __P010		__pgprot(0)
#define __P011		__pgprot(PTE_READ)
#define __P100		__pgprot(PTE_EXEC)
#define __P101		__pgprot(PTE_EXEC | PTE_READ)
#define __P110		__pgprot(PTE_EXEC)
#define __P111		__pgprot(PTE_EXEC | PTE_READ)

#define __S000		__pgprot(0)
#define __S001		__pgprot(PTE_READ)
#define __S010		__pgprot(PTE_WRITE)
#define __S011		__pgprot(PTE_WRITE | PTE_READ)
#define __S100		__pgprot(PTE_EXEC)
#define __S101		__pgprot(PTE_EXEC | PTE_READ)
#define __S110		__pgprot(PTE_EXEC | PTE_WRITE)
#define __S111		__pgprot(PTE_RWX)
