#include <linux/linkage.h>
#include <arch/asm-common.h>
#include <generated/asm-offsets.h>

/**
 * __switch_to - Register switch for UniCore3 processors
 * @prev:	previous task_struct in r0
 * @next:	next task_struct in r1
 */
ENTRY(__switch_to)
	@ Calculate cpu_context position of prev task
	dadd	ip, r0, #TASK_THREAD + THREAD_CPU_CONTEXT

	@ Save all callee-saved registers, from r16 to r27
	@ Save stack pointer(r29) and return address(r30)
	.irp	n, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 29, 30
	std.w	r\n, [ip]+, #8
	.endr

	@ Now, switch to another thread

	@ Calculate cpu_context position of next task
	dadd	ip, r1, #TASK_THREAD + THREAD_CPU_CONTEXT

	@ Restore all callee-saved registers, from r16 to r27
	@ Restore stack pointer(r29) and return address(r30)

	.irp	n, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 29, 30
	ldd.w	r\n, [ip]+, #8
	.endr

	return
ENDPROC(__switch_to)
