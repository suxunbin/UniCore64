#ifndef __UNICORE64_ARCH_ASM_MMUOPS_H__
#define __UNICORE64_ARCH_ASM_MMUOPS_H__

#include <arch/asm-common.h>

/**
 * uc64_invalidate_dcache - invalidate entire L1 dcache
 */
__ASMMACRO_WRAP(.macro	uc64_invalidate_dcache, rt;
			dmovl	&rt, #0;
			movc	p0.c6, &rt, #8;
		.endm)

/**
 * uc64_flush_dcache - flush entire L1 dcache
 */
__ASMMACRO_WRAP(.macro	uc64_flush_dcache, rt;
			dmovl	&rt, #0;
			movc	p0.c6, &rt, #12;
		.endm)

/**
 * uc64_invalidate_icache - invalidate entire icache
 */
__ASMMACRO_WRAP(.macro	uc64_invalidate_icache, rt;
			dmovl	&rt, #0;
			movc	p0.c7, &rt, #0;
		.endm)

/**
 * uc64_invalidate_tlb - invalidate I&D tlb
 */
__ASMMACRO_WRAP(.macro	uc64_invalidate_tlb, rt;
			dmovl	&rt, #0;
			movc	p0.c5, &rt, #24;
		.endm)

/**
 * uc64_enable_dcache -  enable dcache
 */
__ASMMACRO_WRAP(.macro	uc64_enable_dcache, rt;
#ifndef CONFIG_CPU_DCACHE_DISABLE
			movc	&rt, p0.c1, #0;
			dor	&rt, &rt, #4;
			movc	p0.c1, &rt, #0;
#endif
		.endm)

/**
 * uc64_enable_icache -  enable icache
 */
__ASMMACRO_WRAP(.macro	uc64_enable_icache, rt;
#ifndef CONFIG_CPU_ICACHE_DISABLE
			movc	&rt, p0.c1, #0;
			dor	&rt, &rt, #8;
			movc	p0.c1, &rt, #0;
#endif
		.endm)

/**
 * uc64_set_pgd -  set pgd address
 */
__ASMMACRO_WRAP(.macro	uc64_set_pgd, rpgd;
			movc	p0.c2, &rpgd, #0;
		.endm)

#endif /* __UNICORE64_ARCH_ASM_MMUOPS_H__ */
