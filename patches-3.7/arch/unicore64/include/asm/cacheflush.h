#ifndef __UNICORE64_ASM_CACHEFLUSH_H__
#define __UNICORE64_ASM_CACHEFLUSH_H__

/* Keep includes the same across arches.  */
#include <linux/mm.h>
#include <arch/asm-mmuops.h>

#define flush_cache_all()			\
	do {					\
		__flush_dcache();		\
		__invalid_icache();		\
	} while (0)
#define flush_cache_mm(mm)			flush_cache_all()
#define flush_cache_dup_mm(mm)			flush_cache_all()
#define flush_cache_range(vma, start, end)	flush_cache_all()
#define flush_cache_page(vma, vmaddr, pfn)	flush_cache_all()
#define ARCH_IMPLEMENTS_FLUSH_DCACHE_PAGE 1
#define flush_dcache_page(page)			__flush_dcache()
#define flush_dcache_mmap_lock(mapping)		do { } while (0)
#define flush_dcache_mmap_unlock(mapping)	do { } while (0)
#define flush_icache_range(start, end)		flush_cache_all()
#define flush_icache_page(vma,pg)		flush_cache_all()
#define flush_icache_user_range(vma,pg,adr,len)	flush_cache_all()
#define flush_cache_vmap(start, end)		do { } while (0)
#define flush_cache_vunmap(start, end)		do { } while (0)

#define copy_to_user_page(vma, page, vaddr, dst, src, len)	\
	do {							\
		memcpy(dst, src, len);				\
		flush_icache_user_range(vma, page, vaddr, len);	\
	} while (0)
#define copy_from_user_page(vma, page, vaddr, dst, src, len)	\
	memcpy(dst, src, len)

#endif /* __UNICORE64_ASM_CACHEFLUSH_H__ */
