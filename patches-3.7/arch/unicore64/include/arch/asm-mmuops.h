#ifndef __UNICORE64_ARCH_ASM_MMUOPS_H__
#define __UNICORE64_ARCH_ASM_MMUOPS_H__

#include <arch/asm-common.h>

/**
 * uc64_invalidate_dcache - invalidate entire L1 dcache
 */
__ASMMACRO_WRAP(.macro uc64_invalidate_dcache, rt;
			dmovl	&rt, #0;
			movc	cp0.c6, &rt, #8;
		.endm)

/**
 * uc64_flush_dcache - flush entire L1 dcache
 */
__ASMMACRO_WRAP(.macro uc64_flush_dcache, rt;
			dmovl	&rt, #0;
			movc	cp0.c6, &rt, #12;
		.endm)

/**
 * uc64_invalidate_icache - invalidate entire icache
 */
__ASMMACRO_WRAP(.macro uc64_invalidate_icache, rt;
			dmovl	&rt, #0;
			movc	cp0.c7, &rt, #0;
		.endm)

/**
 * uc64_invalidate_tlb - invalidate I&D tlb
 */
__ASMMACRO_WRAP(.macro uc64_invalidate_tlb, rt;
			dmovl	&rt, #0;
			movc	cp0.c5, &rt, #24;
		.endm)

#endif /* __UNICORE64_ARCH_ASM_MMUOPS_H__ */
