#ifndef __UNICORE64_ARCH_ASM_COMMON_H__
#define __UNICORE64_ARCH_ASM_COMMON_H__

#include <linux/stringify.h>
#include <arch/hwdef-cpu.h>
/*
 * __ASMMACRO_WRAP is ONLY used for assembly macro definitions.
 * Then this macro could be used in both assembly files and c files.
 */
#ifdef __ASSEMBLY__
#define __ASMMACRO_WRAP(code...)	code
#else
#define __ASMMACRO_WRAP(code...)	__asm__(__stringify(code));
#endif /* __ASSEMBLY__ */

__ASMMACRO_WRAP(.macro	__push, rt;
			std.w	&rt, [sp-], #8;
		.endm)

__ASMMACRO_WRAP(.macro	__pop, rt;
			ldd.w	&rt, [sp]+, #8;
		.endm)

__ASMMACRO_WRAP(.macro	__halt;
			halt;
		.endm)

__ASMMACRO_WRAP(.macro	__sync;
			sync;
		.endm)

__ASMMACRO_WRAP(.macro	__irq_disable;
			dmov	r16, asr;
			dor	r16, r16, #ASR_INTR_SELECT;
			dmov	asr, r16;
		.endm)

__ASMMACRO_WRAP(.macro	__irq_enable;
			dmov	r16, asr;
			dand	r16, r16, #(~ASR_INTR_SELECT);
			dmov	asr, r16;
		.endm)

#define __halt()			__asm__ __volatile__("__halt")
#define __sync()			__asm__ __volatile__("__sync")

/*
 * We use "____" prefix(4 '_') only for debug:
 *  All definitions here should be removed definitely and completely.
 */
#ifdef __ASSEMBLY__
#define ____align64			.p2align 3
#endif /* __ASSEMBLY__ */

#endif /* __UNICORE64_ARCH_ASM_COMMON_H__ */
