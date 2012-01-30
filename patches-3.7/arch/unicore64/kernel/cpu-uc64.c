#include <linux/kernel.h>
#include <linux/seq_file.h>

#include <asm/setup_arch.h>

#include <arch/hwdef-cpu.h>
#include <arch/hwdef-cp0-sysctrl.h>

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
 * setup_arch_cpuinfo() - show the cpu and cache information
 *
 * show the cpu and cache information in the screen.
 * first, get the value in copro through the macro UC64_CPUID,
 * then check the bit field. The value should be 0x4Duv0863. It represent
 * that designer is 0x4D, series is 0xu, layout is 0xv, and
 * part number is 0x0863. And the layout value is not checked here.
 * And then, get the cache information from the macro UC64_CACHETYPE,
 * judge the strategy, such as I&D cache seperate, lockdown, write back
 * and write throuth, if it was enabled. At last, print out the information
 * of Instruct cache and Date cache.
 */
#define CACHETYPE_SIZE(CT)						\
	switch (uc64_cache & CP0_CPUID_##CT##CACHE_SIZE_SELECT) {	\
	case CP0_CPUID_##CT##CACHE_SIZE_512B:				\
		pr_info("512B "); break;				\
	case CP0_CPUID_##CT##CACHE_SIZE_1KB:				\
		pr_info("1KB "); break;					\
	case CP0_CPUID_##CT##CACHE_SIZE_2KB:				\
		pr_info("2KB "); break;					\
	case CP0_CPUID_##CT##CACHE_SIZE_4KB:				\
		pr_info("4KB "); break;					\
	case CP0_CPUID_##CT##CACHE_SIZE_8KB:				\
		pr_info("8KB "); break;					\
	case CP0_CPUID_##CT##CACHE_SIZE_16KB:				\
		pr_info("16KB "); break;				\
	case CP0_CPUID_##CT##CACHE_SIZE_32KB:				\
		pr_info("32KB "); break;				\
	case CP0_CPUID_##CT##CACHE_SIZE_64KB:				\
		pr_info("64KB "); break;				\
	}

#define CACHETYPE_ASSOC(CT)						\
	switch (uc64_cache & CP0_CPUID_##CT##CACHE_ASSOC_SELECT) {	\
	case CP0_CPUID_##CT##CACHE_ASSOC_DMAP:				\
		pr_info("DMAP "); break;				\
	case CP0_CPUID_##CT##CACHE_ASSOC_2WAY:				\
		pr_info("2Way "); break;				\
	case CP0_CPUID_##CT##CACHE_ASSOC_4WAY:				\
		pr_info("4Way "); break;				\
	case CP0_CPUID_##CT##CACHE_ASSOC_8WAY:				\
		pr_info("8Way "); break;				\
	case CP0_CPUID_##CT##CACHE_ASSOC_16WAY:				\
		pr_info("16Way "); break;				\
	case CP0_CPUID_##CT##CACHE_ASSOC_32WAY:				\
		pr_info("32Way "); break;				\
	case CP0_CPUID_##CT##CACHE_ASSOC_64WAY:				\
		pr_info("64Way "); break;				\
	case CP0_CPUID_##CT##CACHE_ASSOC_128WAY:			\
		pr_info("128Way "); break;				\
	}

#define CACHETYPE_LINE(CT)						\
	switch (uc64_cache & CP0_CPUID_##CT##CACHE_LINE_SELECT) {	\
	case CP0_CPUID_##CT##CACHE_LINE_8BYTE:				\
		pr_info("L8B"); break;					\
	case CP0_CPUID_##CT##CACHE_LINE_16BYTE:				\
		pr_info("L16B"); break;					\
	case CP0_CPUID_##CT##CACHE_LINE_32BYTE:				\
		pr_info("L32B"); break;					\
	case CP0_CPUID_##CT##CACHE_LINE_64BYTE:				\
		pr_info("L64B"); break;					\
	}

void __init setup_arch_cpuinfo(void)
{
	unsigned long uc64_cpuid;
	unsigned long uc64_cache;

	uc64_cpuid = __read_cp_op(CP0_CPUID, 0);

	BUG_ON((uc64_cpuid & CP0_CPUID_PARTNO_SELECT) !=
			CP0_CPUID_PARTNO_PKUNITY);

	BUG_ON((uc64_cpuid & CP0_CPUID_DESIGNER_SELECT) !=
			CP0_CPUID_DESIGNER_MPRC);

	pr_info("CPU: UniCore64, Designer: MPRC, SoC: PKUnity,");
	pr_info(" revision: %ld, layout: %ld\n",
		((uc64_cpuid & CP0_CPUID_SERIES_SELECT) >> CP0_CPUID_SERIES_POS),
		((uc64_cpuid & CP0_CPUID_LAYOUT_SELECT) >> CP0_CPUID_LAYOUT_POS));

	/* CACHE information */
	uc64_cache = __read_cp_op(CP0_CPUID, 1);

	BUG_ON(!(uc64_cache & CP0_CPUID_CACHE_SEPERATE));

	pr_info("Cachetype: %s %s, ",
		(uc64_cache & CP0_CPUID_CACHE_LOCKDOWN) ? "LD" : NULL,
		(uc64_cache & CP0_CPUID_CACHE_WRITEBACK) ? "WB" : "WT");

	pr_info("I$: ");
	CACHETYPE_SIZE(I);
	CACHETYPE_ASSOC(I);
	CACHETYPE_LINE(I);

	pr_info(", D$: ");
	CACHETYPE_SIZE(D);
	CACHETYPE_ASSOC(D);
	CACHETYPE_LINE(D);

	pr_info("\n");
}

#undef CACHETYPE_SIZE
#undef CACHETYPE_ASSOC
#undef CACHETYPE_LINE

void show_uc64_info(void)
{
	pr_emerg("\nUniCore64 Information:\n");
	pr_emerg(" ASR BSR: %16lx %16lx\n", __read_uc64(asr), __read_uc64(bsr));
	pr_emerg(" AFR BFR: %16lx %16lx\n", __read_uc64(afr), __read_uc64(bfr));
}
