#ifndef __ASSEMBLY__
#error "Only include this from assembly code"
#endif

#define csub		cmpsub

	.macro	nop8
	.rept	8
		nop
	.endr
	.endm
