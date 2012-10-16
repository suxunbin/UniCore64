#ifndef __UNICORE64_ASM_LINKAGE_H__
#define __UNICORE64_ASM_LINKAGE_H__

#define ENDPROC(name)		\
	.type name, %function;	\
	END(name)

/* FIXME */
#define __lock_aligned __attribute__((aligned(8)))

#endif /* __UNICORE64_ASM_LINKAGE_H__ */
