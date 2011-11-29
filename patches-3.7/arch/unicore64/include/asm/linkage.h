#ifndef __UNICORE64_ASM_LINKAGE_H__
#define __UNICORE64_ASM_LINKAGE_H__

#define ENDPROC(name)		\
	.type name, %function;	\
	END(name)

#endif /* __UNICORE64_ASM_LINKAGE_H__ */
