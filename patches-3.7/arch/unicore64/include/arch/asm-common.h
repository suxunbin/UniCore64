#ifndef __UNICORE64_ARCH_ASM_COMMON_H__
#define __UNICORE64_ARCH_ASM_COMMON_H__

#define csub		cmpsub

/*
 * __ASM_WRAP is ONLY used for assembly macro definitions.
 * Then this macro could be used in both assembly files and c files.
 */
#ifdef __ASSEMBLY__
#define __ASM_WRAP(code...)	code
#else
#define __ASM_WRAP(code...)	__asm__(#code);
#endif /* __ASSEMBLY__ */

#endif /* __UNICORE64_ARCH_ASM_COMMON_H__ */
