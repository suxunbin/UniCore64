#include <linux/linkage.h>
#include <arch/asm-common.h>

ENTRY(mcount)
	__push	r0
	__push	r1
	ldd     r1, [ip-], #8
        dsub    r1, r1, #4
	mov	r0, #0
	bkpt
	__pop	r1
	__pop	r0
	return
ENDPROC(mcount)
