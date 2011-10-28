#include <linux/kernel.h>

/**
 * machine_restart() - Reboot the machine
 * @cmd:
 */
void machine_restart(char *cmd)
{
	/* FIXME */
	BUG();
}

/**
 * machine_halt() - Halt the machine
 */
void machine_halt(void)
{
	/* FIXME */
	BUG();
}

/**
 * machine_power_off() - Power off the machine
 */
void machine_power_off(void)
{
	/* FIXME */
	BUG();
}

/**
 * Function pointers to optional machine specific functions
 */
void (*pm_power_off)(void) = NULL;
