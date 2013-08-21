#include <arch/hwdef-cp0-sysctrl.h>
#include <arch/hwdef-cpu.h>
#include <arch/asm-common.h>

/*
 * __head_init - Initialize asr and coprocessor0.
 *
 * Initialize ASR which is in PRIV mode and keep INTR off
 *
 * Initialize control register of coprocessor 0.
 * setup common bits before finally enabling the MMU.
 * .... .... ..BS IDAM
 * .... .... ..10 0000
 */
.macro	__head_init
	dmovl		r16, #ASR_MODE_PRIV | ASR_INTR_SELECT | ASR_T_BIT
	dmov		asr, r16
	dmov		r16, #CP0_CTRLREG_DEFAULT
	movc		CP0_CTRLREG, r16, #0
.endm

/*
 * __clear_bss - Clear bss region
 *
 * All GP registers will be destroyed in this macro.
 */
.macro	__clear_bss
	adr		r1, 1001f
	ldd		r0, [r1+], #0
	ldd		r2, [r1+], #8
	dsub		r2, r2, r0
	dmov		r1, #0
	adr		lr, 1002f
	b		memset

	____align64
1001:
	.dword	__bss_start
	.dword	_end
1002:
.endm

/*
 * __cache_init - invalid and enable icache and dcache
 */
.macro	__cache_init
	__invalid_dcache
	__invalid_icache

	movc		r16, p0.c1, #0;
#ifndef CONFIG_CPU_DCACHE_DISABLE
	dor		r16, r16, #4;
#endif
#ifndef CONFIG_CPU_ICACHE_DISABLE
	dor		r16, r16, #8;
#endif
	movc		p0.c1, r16, #0;
.endm

/*
 * __enable_mmu - enable MMU
 */
.macro	__enable_mmu
	movc		r16, CP0_CTRLREG, #0
	dor		r16, r16, #CP0_CTRLREG_MMU
#ifdef	CONFIG_ALIGNMENT_TRAP
	dor		r16, r16, #CP0_CTRLREG_ALIGN
#endif
	movc		CP0_CTRLREG, r16, #0
.endm
