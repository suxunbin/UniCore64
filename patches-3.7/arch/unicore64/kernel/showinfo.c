#include <linux/kernel.h>
#include <linux/elfcore.h>
#include <linux/bug.h>
#include <linux/sched.h>

#include <asm/setup_arch.h>

#include <arch/hwdef-cpu.h>
#include <arch/hwdef-cp0-sysctrl.h>

void __show_uc64_regs(void)
{
	pr_emerg("\nUniCore64 Information:\n");
	pr_emerg(" ASR BSR: %16lx %16lx\n", __read_uc64(asr), __read_uc64(bsr));
	pr_emerg(" AFR BFR: %16lx %16lx\n", __read_uc64(afr), __read_uc64(bfr));
}

/**
 * __show_cpuinfo() - show the cpu and cache information
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
		printk(KERN_CONT "512B "); break;			\
	case CP0_CPUID_##CT##CACHE_SIZE_1KB:				\
		printk(KERN_CONT "1KB "); break;			\
	case CP0_CPUID_##CT##CACHE_SIZE_2KB:				\
		printk(KERN_CONT "2KB "); break;			\
	case CP0_CPUID_##CT##CACHE_SIZE_4KB:				\
		printk(KERN_CONT "4KB "); break;			\
	case CP0_CPUID_##CT##CACHE_SIZE_8KB:				\
		printk(KERN_CONT "8KB "); break;			\
	case CP0_CPUID_##CT##CACHE_SIZE_16KB:				\
		printk(KERN_CONT "16KB "); break;			\
	case CP0_CPUID_##CT##CACHE_SIZE_32KB:				\
		printk(KERN_CONT "32KB "); break;			\
	case CP0_CPUID_##CT##CACHE_SIZE_64KB:				\
		printk(KERN_CONT "64KB "); break;			\
	}

#define CACHETYPE_ASSOC(CT)						\
	switch (uc64_cache & CP0_CPUID_##CT##CACHE_ASSOC_SELECT) {	\
	case CP0_CPUID_##CT##CACHE_ASSOC_DMAP:				\
		printk(KERN_CONT "DMAP "); break;			\
	case CP0_CPUID_##CT##CACHE_ASSOC_2WAY:				\
		printk(KERN_CONT "2Way "); break;			\
	case CP0_CPUID_##CT##CACHE_ASSOC_4WAY:				\
		printk(KERN_CONT "4Way "); break;			\
	case CP0_CPUID_##CT##CACHE_ASSOC_8WAY:				\
		printk(KERN_CONT "8Way "); break;			\
	case CP0_CPUID_##CT##CACHE_ASSOC_16WAY:				\
		printk(KERN_CONT "16Way "); break;			\
	case CP0_CPUID_##CT##CACHE_ASSOC_32WAY:				\
		printk(KERN_CONT "32Way "); break;			\
	case CP0_CPUID_##CT##CACHE_ASSOC_64WAY:				\
		printk(KERN_CONT "64Way "); break;			\
	case CP0_CPUID_##CT##CACHE_ASSOC_128WAY:			\
		printk(KERN_CONT "128Way "); break;			\
	}

#define CACHETYPE_LINE(CT)						\
	switch (uc64_cache & CP0_CPUID_##CT##CACHE_LINE_SELECT) {	\
	case CP0_CPUID_##CT##CACHE_LINE_8BYTE:				\
		printk(KERN_CONT "L8B"); break;				\
	case CP0_CPUID_##CT##CACHE_LINE_16BYTE:				\
		printk(KERN_CONT "L16B"); break;			\
	case CP0_CPUID_##CT##CACHE_LINE_32BYTE:				\
		printk(KERN_CONT "L32B"); break;			\
	case CP0_CPUID_##CT##CACHE_LINE_64BYTE:				\
		printk(KERN_CONT "L64B"); break;			\
	}

void __show_cpuinfo(void)
{
	unsigned long uc64_cpuid;
	unsigned long uc64_cache;

	uc64_cpuid = __read_cp_op(CP0_CPUID, 0);

	BUG_ON((uc64_cpuid & CP0_CPUID_PARTNO_SELECT) !=
			CP0_CPUID_PARTNO_PKUNITY);

	BUG_ON((uc64_cpuid & CP0_CPUID_DESIGNER_SELECT) !=
			CP0_CPUID_DESIGNER_MPRC);

	pr_info("CPU: UniCore64, Designer: MPRC, SoC: PKUnity,");
	printk(KERN_CONT " revision: %ld, layout: %ld\n",
		((uc64_cpuid & CP0_CPUID_SERIES_SELECT) >> CP0_CPUID_SERIES_POS),
		((uc64_cpuid & CP0_CPUID_LAYOUT_SELECT) >> CP0_CPUID_LAYOUT_POS));

	/* CACHE information */
	uc64_cache = __read_cp_op(CP0_CPUID, 1);

	BUG_ON(!(uc64_cache & CP0_CPUID_CACHE_SEPERATE));

	pr_info("Cachetype:%s %s, ",
		(uc64_cache & CP0_CPUID_CACHE_LOCKDOWN) ? " LD" : "",
		(uc64_cache & CP0_CPUID_CACHE_WRITEBACK) ? "WB" : "WT");

	printk(KERN_CONT "I$: ");
	CACHETYPE_SIZE(I);
	CACHETYPE_ASSOC(I);
	CACHETYPE_LINE(I);

	printk(KERN_CONT ", D$: ");
	CACHETYPE_SIZE(D);
	CACHETYPE_ASSOC(D);
	CACHETYPE_LINE(D);
}

#undef CACHETYPE_SIZE
#undef CACHETYPE_ASSOC
#undef CACHETYPE_LINE
void __show_cp0_regs(void)
{
	pr_emerg("\nCP0 (System Control) Information:\n");
	pr_emerg(" CPUID:      %16lx\n", __read_cp_op(CP0_CPUID, 0));
	pr_emerg(" CACHE:      %16lx\n", __read_cp_op(CP0_CPUID, 1));
	pr_emerg(" CTRLREG:    %16lx\n", __read_cp(CP0_CTRLREG));
	pr_emerg(" TTB/ASID:   %16lx\n", __read_cp(CP0_TTB_ASID));
	pr_emerg(" ITRAPSTAT:  %16lx\n", __read_cp_op(CP0_TRAPSTAT, 0));
	pr_emerg(" DTRAPSTAT:  %16lx\n", __read_cp_op(CP0_TRAPSTAT, 1));
	pr_emerg(" ITRAPADDR:  %16lx\n", __read_cp_op(CP0_TRAPADDR, 1));
	pr_emerg(" DTRAPADDR:  %16lx\n", __read_cp_op(CP0_TRAPADDR, 0));

	pr_emerg(" MRAR_BASE:  %16lx %16lx %16lx %16lx\n",
			__read_cp_op(CP0_MRAR, 0),
			__read_cp_op(CP0_MRAR, 1),
			__read_cp_op(CP0_MRAR, 2),
			__read_cp_op(CP0_MRAR, 3));
	pr_emerg(" (Total 8):  %16lx %16lx %16lx %16lx\n",
			__read_cp_op(CP0_MRAR, 4),
			__read_cp_op(CP0_MRAR, 5),
			__read_cp_op(CP0_MRAR, 6),
			__read_cp_op(CP0_MRAR, 7));
	pr_emerg(" MRAR_MASK:  %16lx %16lx %16lx %16lx\n",
			__read_cp_op(CP0_MRAR, 8),
			__read_cp_op(CP0_MRAR, 9),
			__read_cp_op(CP0_MRAR, 10),
			__read_cp_op(CP0_MRAR, 11));
	pr_emerg(" (Total 8):  %16lx %16lx %16lx %16lx\n",
			__read_cp_op(CP0_MRAR, 12),
			__read_cp_op(CP0_MRAR, 13),
			__read_cp_op(CP0_MRAR, 14),
			__read_cp_op(CP0_MRAR, 15));

	pr_emerg(" VECBASE:    %16lx\n", __read_cp(CP0_VECBASE));
	pr_emerg(" INTR_TYPE:  %16lx\n", __read_cp_op(CP0_INTR, 0));
	pr_emerg(" INTR_PRIO:  %16lx\n", __read_cp_op(CP0_INTR, 7));
	pr_emerg(" ITM_CNTR:   %16lx\n", __read_cp_op(CP0_INTR, 9));
	pr_emerg(" ITM_MATCH:  %16lx\n", __read_cp_op(CP0_INTR, 10));

	pr_emerg(" R/W Margin: %16lx\n", __read_cp(CP0_RWMARGIN));
}

/**
 * dump_fpu() -
 * @regs:
 * @fp:
 */
int dump_fpu(struct pt_regs *regs, elf_fpregset_t *fp)
{
	/* FIXME: fill in the fpe structure for a core dump... */
	BUG();
	return 0;
}

/**
 * show_regs() -
 * @regs:
 */
void show_regs(struct pt_regs *regs)
{
	/* FIXME */
	BUG();
}

/**
 * show_stack() -
 * @tsk:
 * @sp:
 */
void show_stack(struct task_struct *tsk, unsigned long *sp)
{
	/* FIXME */
	BUG();
}
