#include <linux/kernel.h>

/**
 * kernel_execve() -
 * @filename:
 * @argv:
 * @envp:
 */
int kernel_execve(const char *filename,
		  const char *const argv[],
		  const char *const envp[])
{
	/* FIXME */
	BUG();
	return 0;
}