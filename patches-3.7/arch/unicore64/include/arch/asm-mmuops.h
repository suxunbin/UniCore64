#ifndef __UNICORE64_ARCH_ASM_MMUOPS_H__
#define __UNICORE64_ARCH_ASM_MMUOPS_H__

/**
 * DOC: ASM_MMUOPS_H
 * This file defines MMU wraps such as invalidate icache,
 * dcache, or tlb.
 */
#include <arch/asm-common.h>

/**
 * DOC: ASM_MMUOPS_H_INVALIDATE_DCACHE
 * uc64_invalidate_dcache - invalidate entire L1 dcache
 */
__ASMMACRO_WRAP(.macro	uc64_invalidate_dcache, rt;
			dmovl	&rt, #0;
			movc	p0.c6, &rt, #8;
		.endm)

/**
 * DOC: ASM_MMUOPS_H_FLUSH_DCACHE
 * uc64_flush_dcache - flush entire L1 dcache
 */
__ASMMACRO_WRAP(.macro	uc64_flush_dcache, rt;
			dmovl	&rt, #0;
			movc	p0.c6, &rt, #12;
		.endm)

/**
 * DOC: ASM_MMUOPS_H_INVALIDATE_ICACHE
 * uc64_invalidate_icache - invalidate entire icache
 */
__ASMMACRO_WRAP(.macro	uc64_invalidate_icache, rt;
			dmovl	&rt, #0;
			movc	p0.c7, &rt, #0;
		.endm)

/**
 * DOC: ASM_MMUOPS_H_INVALIDATE_TLB
 * uc64_invalidate_tlb - invalidate I&D tlb
 */
__ASMMACRO_WRAP(.macro	uc64_invalidate_tlb, rt;
			dmovl	&rt, #0;
			movc	p0.c5, &rt, #24;
		.endm)

/**
 * DOC: ASM_MMUOPS_H_SET_PGD
 * uc64_set_pgd -  set pgd address
 */
__ASMMACRO_WRAP(.macro	uc64_set_pgd, rpgd;
			movc	p0.c2, &rpgd, #0;
		.endm)

#endif /* __UNICORE64_ARCH_ASM_MMUOPS_H__ */
