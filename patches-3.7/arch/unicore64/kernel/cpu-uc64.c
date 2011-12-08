#include <linux/kernel.h>
#include <linux/seq_file.h>

/**
 * cpu_ucv3_show() -
 * @m:
 * @v:
 */
static int cpu_ucv3_show(struct seq_file *m, void *v)
{
	/* FIXME */
	BUG();
	return 0;
}

/**
 * cpu_ucv3_start() -
 * @m:
 * @pos:
 */
static void *cpu_ucv3_start(struct seq_file *m, loff_t *pos)
{
	/* FIXME */
	BUG();
}

/**
 * cpu_ucv3_next() -
 * @v:
 * @pos:
 */
static void *cpu_ucv3_next(struct seq_file *m, void *v, loff_t *pos)
{
	/* FIXME */
	BUG();
}

/**
 * cpu_ucv3_stop() -
 * @m:
 * @v:
 */
static void cpu_ucv3_stop(struct seq_file *m, void *v)
{
	/* FIXME */
	BUG();
}

/**
 * struct cpuinfo_op -
 * @start:
 * @next:
 * @stop:
 * @show:
 */
const struct seq_operations cpuinfo_op = {
	.start	= cpu_ucv3_start,
	.next	= cpu_ucv3_next,
	.stop	= cpu_ucv3_stop,
	.show	= cpu_ucv3_show
};
