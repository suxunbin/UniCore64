#include <arch/hwdef-cp0-sysctrl.h>
#include <arch/hwdef-cpu.h>
#include <arch/asm-common.h>

/*
 * __head_initialize - Initialize asr and coprocessor0.
 *
 * Initialize ASR which is in PRIV mode and keep INTR off
 *
 * Initialize control register of coprocessor 0.
 * setup common bits before finally enabling the MMU.
 * .... .... ..BS IDAM
 * .... .... ..10 0000
 */
.macro	__head_initialize, rt
	dmovl	&rt, #ASR_MODE_PRIV | ASR_INTR_SELECT
	dmov	asr, &rt
	dmov	&rt, #CP0_CTRLREG_DEFAULT
	movc	CP0_CTRLREG, &rt, #0
.endm

/*
 * __head_clear_bss - Clear bss region
 *
 * r0, r1 and r2 will be used in this macro.
 */
.macro	__head_clear_bss
	adr	r1, 1001f
	ldd	r0, [r1+], #0
	ldd	r2, [r1+], #8
	dsub	r2, r2, r0
	dmov	r1, #0
	adr	lr, 1002f
	b	memset

	____align64
1001:
	.dword	__bss_start
	.dword	_end
1002:
.endm

/*
 * uc64_enable_cache - enable entire icache and dcache
 */
.macro	uc64_enable_cache, rt
	movc	&rt, p0.c1, #0;
#ifndef CONFIG_CPU_DCACHE_DISABLE
	dor	&rt, &rt, #4;
#endif
#ifndef CONFIG_CPU_ICACHE_DISABLE
	dor	&rt, &rt, #8;
#endif
	movc	p0.c1, &rt, #0;
.endm
