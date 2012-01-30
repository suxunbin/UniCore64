#include <linux/kernel.h>
#include <linux/init.h>

#include <arch/hwdef-cpu.h>
#include <arch/hwdef-cp0-sysctrl.h>

/**
 * init_IRQ() -
 */
void __init init_IRQ(void)
{
	/* Disable and clear all uc64 interrupts */
	__write_uc64(__read_uc64(asr) | ASR_INTR_SELECT, asr);
	__write_cp(0, CP0_INTR);
}
