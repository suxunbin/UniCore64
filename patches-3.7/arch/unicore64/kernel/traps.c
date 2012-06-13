#include <linux/kernel.h>
#include <linux/init.h>

#include <asm/setup_arch.h>

#include <arch/hwdef-cp0-sysctrl.h>

/**
 * trap_init() -
 */
void __init trap_init(void)
{
	__write_cp(__vectors_table, CP0_VECBASE);
}
