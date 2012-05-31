#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/notifier.h>
#include <linux/string.h>
#include <linux/of_fdt.h>
#include <linux/console.h>

#include <asm/setup.h>
#include <asm/setup_arch.h>

static char __initdata builtin_cmdline[COMMAND_LINE_SIZE] = CONFIG_CMDLINE;

static int uc64_panic_event(struct notifier_block *this,
		unsigned long event, void *ptr)
{
	__show_uc64_regs();
	__show_cp0_regs();

	return NOTIFY_DONE;
}

static struct notifier_block uc64_panic_block = {
	uc64_panic_event,
	NULL,
	INT_MAX /* try to do it first */
};

static void __init setup_arch_param(char **cmdline_p)
{
	setup_arch_devtree(boot_command_line);

	if (boot_command_line[0])
		strlcat(boot_command_line, " ", COMMAND_LINE_SIZE);
	strlcat(boot_command_line, builtin_cmdline, COMMAND_LINE_SIZE);

	strlcpy(builtin_cmdline, boot_command_line, COMMAND_LINE_SIZE);
	*cmdline_p = builtin_cmdline;
}

/**
 * setup_arch() - Architecture-specific boot-time initializations
 * @cmdline_p:
 */
void __init setup_arch(char **cmdline_p)
{
	/* Register a call for panic conditions. */
	atomic_notifier_chain_register(&panic_notifier_list,
			&uc64_panic_block);

	setup_arch_cpuinfo();
	setup_arch_param(cmdline_p);
	setup_arch_memory();
	unflatten_device_tree();

	/* Set default console for virtual terminal */
#if defined(CONFIG_OCD_CONSOLE)
	conswitchp = &ocd_con;
#elif defined(CONFIG_DUMMY_CONSOLE)
	conswitchp = &dummy_con;
#endif
}
