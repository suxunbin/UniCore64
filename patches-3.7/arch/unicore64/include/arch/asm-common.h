#ifndef __UNICORE64_ARCH_ASM_COMMON_H__
#define __UNICORE64_ARCH_ASM_COMMON_H__

#define csub		cmpsub

/*
 * __ASMMACRO_WRAP is ONLY used for assembly macro definitions.
 * Then this macro could be used in both assembly files and c files.
 */
#ifdef __ASSEMBLY__
#define __ASMMACRO_WRAP(code...)	code
#else
#define __ASMMACRO_WRAP(code...)	__asm__(#code);
#endif /* __ASSEMBLY__ */

#endif /* __UNICORE64_ARCH_ASM_COMMON_H__ */
