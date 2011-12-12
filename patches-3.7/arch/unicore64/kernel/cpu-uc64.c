#include <linux/kernel.h>
#include <linux/seq_file.h>

#include <asm/setup_arch.h>

#include <arch/hwdef-copro.h>

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

/**
 * setup_arch_cpuinfo() - show the cpu information
 *
 * show the cpu information in the screen.
 * first, get the value in copro through the macro UC64_CPUID,
 * then check the bit field. The value should be 0x4Duv0863. It represent
 * that designer is 0x4D, series is 0xu, layout is 0xv, and
 * part number is 0x0863. And the layout value is not checked here.
 */
void __init setup_arch_cpuinfo(void)
{
	unsigned long uc64_cpuid;

	uc64_cpuid = UC64_CPUID;

	BUG_ON((uc64_cpuid & CP0_CPUID_PARTNO_MASK) !=
			CP0_CPUID_PARTNO_PKUNITY);

	BUG_ON((uc64_cpuid & CP0_CPUID_DESIGNER_MASK) !=
			CP0_CPUID_DESIGNER_MPRC);

	pr_info("CPU: UniCore64, Designer: MPRC, SoC: PKUnity\n");
	pr_info("revision: %ld, layout: %ld\n",
		((uc64_cpuid & CP0_CPUID_SERIES_MASK) >> CP0_CPUID_SERIES_POS),
		((uc64_cpuid & CP0_CPUID_LAYOUT_MASK) >> CP0_CPUID_LAYOUT_POS));
}
