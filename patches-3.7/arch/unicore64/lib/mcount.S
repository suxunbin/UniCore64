#include <linux/linkage.h>
#include <arch/asm-common.h>
#include <arch/asm-debug.h>

ENTRY(mcount)
	@ Save lr and all parameter registers, from r0 to r3
	.irp		n, 30, 3, 2, 1, 0
	__push		r\n
	.endr

	adr		r0, mcount_info
	dmov		r1, lr
	dmov		r2, lr
	call		printk

	@ Restore lr and all parameter registers, from r0 to r3
	.irp		n, 0, 1, 2, 3, 30
	__pop		r\n
	.endr
	return

mcount_info:		.asciz	"\t[<%016lx>] %pS\n"
ENDPROC(mcount)
