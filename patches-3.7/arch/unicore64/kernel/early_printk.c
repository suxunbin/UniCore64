#include <linux/console.h>
#include <linux/init.h>
#include <linux/string.h>
#include <arch/asm-debug.h>

static void early_ocd_write(struct console *con, const char *s, unsigned n)
{
	uc64_debug_puts(s, n);
}

static struct console early_ocd_console = {
	.name =		"earlyocd",
	.write =	early_ocd_write,
	.flags =	CON_PRINTBUFFER,
	.index =	-1,
};

static int __init setup_early_printk(char *param)
{
	if (!param)
		return 0;

	if (strstr(param, "keep"))
		early_ocd_console.flags &= ~CON_BOOT;
	else
		early_ocd_console.flags |= CON_BOOT;

	register_console(&early_ocd_console);

	return 0;
}

early_param("earlyprintk", setup_early_printk);
