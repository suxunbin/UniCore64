#include <linux/kernel.h>
#include <linux/seq_file.h>
#include <linux/cpu.h>
#include <linux/percpu.h>

static DEFINE_PER_CPU(struct cpu, cpuinfo_unicore64);

static int __init topology_init(void)
{
	int i;

	for_each_possible_cpu(i) {
		struct cpu *c = &per_cpu(cpuinfo_unicore64, i);
		register_cpu(c, i);
	}

	return 0;
}
subsys_initcall(topology_init);

/**
 * cpu_uc64_show() - show the UniCore64 cpu information
 * @m:		sequence file to output
 * @v:		a pos point for the sequence file
 *
 * Return code:
 * return int type to record the true or false information.
 * 0 - true; not 0 - error.
 *
 * To show the feature of the UniCore64 cpu and cache.
 */
static int cpu_uc64_show(struct seq_file *m, void *v)
{

	/* FIXME */
	BUG();

	return 0;
}

/**
 * cpu_uc64_start() - do init work to the sequence file
 * @m:		sequence file to operate
 * @pos:	the position point for the sequence file
 *
 * Return code:
 * return a void point of the file's position
 *
 * Do some initial work for the operation of the sequence file.
 */
static void *cpu_uc64_start(struct seq_file *m, loff_t *pos)
{
	/* FIXME */
	BUG();

	return NULL;
}

/**
 * cpu_uc64_next() - add the position index for the next data object
 * @m:		sequence file to operate
 * @v:		the index point
 * @pos:	the position point for the sequence file
 *
 * Return code:
 * return a NULL point.
 *
 * Add the position index to access the next data object in the sequence
 * file.
 */
static void *cpu_uc64_next(struct seq_file *m, void *v, loff_t *pos)
{
	/* FIXME */
	BUG();

	return NULL;
}

/**
 * cpu_uc64_stop() - do clean work after finishing the access
 * @m:		sequence file to operate
 * @v:		the index point
 *
 * Do some clean work after finishing the access to the sequence file.
 */
static void cpu_uc64_stop(struct seq_file *m, void *v)
{
	/* FIXME */
	BUG();
}

/*
 * cpuinfo_op is a variable of struct seq_operations type. It's member is
 * the operation for the UniCore cpu information, such as start, next, stop
 * and show.
 */
const struct seq_operations cpuinfo_op = {
	.start	= cpu_uc64_start,
	.next	= cpu_uc64_next,
	.stop	= cpu_uc64_stop,
	.show	= cpu_uc64_show
};
