/*
 * Code specific to PKUnity SoC and UniCore ISA
 *
 * Copyright (C) 2011-2011 GUAN Xuetao
 *
 * Generate definitions needed by assembly language modules.
 * This code generates raw asm output which is post-processed to extract
 * and format the required data.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/kbuild.h>
#include <linux/sched.h>

int main(void)
{
	OFFSET(TASK_THREAD,		task_struct, thread);
	BLANK();

	OFFSET(THREAD_CPU_CONTEXT,	thread_struct, cpu_context);
	BLANK();

	OFFSET(THREAD_INFO_FLAGS,	thread_info, flags);
	return 0;
}
