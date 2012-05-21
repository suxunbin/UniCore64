#include <linux/linkage.h>
#include <arch/asm-common.h>
#include <generated/asm-offsets.h>

/**
 * __switch_to - Register switch for UniCore3 processors
 * @prev:	previous task_struct in r0
 * @next:	next task_struct in r1
 */
ENTRY(__switch_to)
	@ Save all callee-saved registers, from r16 to r27
	.irp	n, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16
	__push	r\n
	.endr

	@ Save stack pointer and return address
	dadd	ip, r0, #TASK_THREAD + THREAD_PC
	std	lr, [ip]
	dadd	ip, r0, #TASK_THREAD + THREAD_KSP
	std	sp, [ip]

	@ Now, switch to another thread

	@ Restore stack pointer and return address
	dadd	ip, r1, #TASK_THREAD + THREAD_PC
	ldd	lr, [ip]
	dadd	ip, r1, #TASK_THREAD + THREAD_KSP
	ldd	sp, [ip]

	@ Restore all callee-saved registers, from r16 to r27
	.irp	n, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27
	__pop	r\n
	.endr

	return
ENDPROC(__switch_to)
