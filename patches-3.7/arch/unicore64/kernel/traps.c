#include <linux/kernel.h>
#include <linux/init.h>

#include <asm/setup_arch.h>

#include <arch/hwdef-cp0-sysctrl.h>

/**
 * trap_init() -
 */
void __init trap_init(void)
{
	write_cp(__vectors_table, CP0_INTR_VECBASE);
}

/**
 * show_stack() -
 * @tsk:
 * @sp:
 */
void show_stack(struct task_struct *tsk, unsigned long *sp)
{
	/* FIXME */
	BUG();
}
