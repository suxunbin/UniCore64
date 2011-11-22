#ifndef __UNICORE64_ARCH_ASM_COMMON_H__
#define __UNICORE64_ARCH_ASM_COMMON_H__

#ifndef __ASSEMBLY__
#error "Only include this from assembly code"
#endif /* __ASSEMBLY__ */

#define csub		cmpsub

	.macro	nop8
	.rept	8
		nop
	.endr
	.endm

#endif /* __UNICORE64_ARCH_ASM_COMMON_H__ */
