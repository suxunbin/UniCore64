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
 * __invalid_dcache - invalidate entire L1 dcache
 * __flush_dcache - flush entire L1 dcache
 * __invalid_icache - invalidate entire icache
 * __invalid_tlb - invalidate I&D tlb
 */
__ASMMACRO_WRAP(.macro	__invalid_dcache;
			dmovl	r16, #0;
			movc	p0.c6, r16, #8;
		.endm)

__ASMMACRO_WRAP(.macro	__flush_dcache;
			dmovl	r16, #0;
			movc	p0.c6, r16, #12;
		.endm)

__ASMMACRO_WRAP(.macro	__invalid_icache;
			dmovl	r16, #0;
			movc	p0.c7, r16, #0;
		.endm)

__ASMMACRO_WRAP(.macro	__invalid_tlb;
			dmovl	r16, #0;
			movc	p0.c5, r16, #24;
		.endm)

#define __invalid_dcache()			__asm__("__invalid_dcache")
#define __invalid_icache()			__asm__("__invalid_icache")
#define __invalid_tlb()				__asm__("__invalid_tlb")
#define __flush_dcache()			__asm__("__flush_dcache")

__ASMMACRO_WRAP(.macro	__invalid_itlb_by_va, rva;
			movc	p0.c5, &rva, #20;
		.endm)

__ASMMACRO_WRAP(.macro	__invalid_dtlb_by_va, rva;
			movc	p0.c5, &rva, #12;
		.endm)

/**
 * DOC: ASM_MMUOPS_H_SET_PGD
 * __set_pgd -  set pgd address
 */
__ASMMACRO_WRAP(.macro	__set_pgd, rpgd;
			movc	p0.c2, &rpgd, #0;
		.endm)

/*
 * __va2pa -  get physical address from virtual address
 * FIXME: There are two exceptions:
 *   if an interrupt occurs just between ldb and movc;
 *   if dtrap occurs at rva address.
 */
__ASMMACRO_WRAP(.macro	__va2pa, rva, rpa;
			ldb	&rpa, [&rva];
			movc	&rpa, p0.c12, #8;
		.endm)
#endif /* __UNICORE64_ARCH_ASM_MMUOPS_H__ */
