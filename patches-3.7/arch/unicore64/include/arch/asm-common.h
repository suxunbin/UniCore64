#ifndef __UNICORE64_ARCH_ASM_COMMON_H__
#define __UNICORE64_ARCH_ASM_COMMON_H__

#include <linux/stringify.h>

#ifdef __ASSEMBLY__
#define csub		cmpsub
#define dcsub		dcmpsub
#endif /* __ASSEMBLY__ */

/*
 * __ASMMACRO_WRAP is ONLY used for assembly macro definitions.
 * Then this macro could be used in both assembly files and c files.
 */
#ifdef __ASSEMBLY__
#define __ASMMACRO_WRAP(code...)	code
#else
#define __ASMMACRO_WRAP(code...)	__asm__(__stringify(code));
#endif /* __ASSEMBLY__ */

__ASMMACRO_WRAP(.macro	uc64_push, rt;
			std.w	&rt, [sp-], #8;
		.endm)

__ASMMACRO_WRAP(.macro	uc64_pop, rt;
			ldd.w	&rt, [sp]+, #8;
		.endm)

/* epip for debug: all should be removed definitely */
#ifdef __ASSEMBLY__
#define __epip4d_align64	.align 3
#endif /* __ASSEMBLY__ */

#endif /* __UNICORE64_ARCH_ASM_COMMON_H__ */
