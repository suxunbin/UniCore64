#include <linux/linkage.h>
#include <arch/asm-common.h>
#include <arch/asm-debug.h>

ENTRY(mcount)
	__push	r0
	ldd     r0, [ip-], #8
        dsub    r0, r0, #4
	__putdata	r0
	__pop	r0
	return
ENDPROC(mcount)
