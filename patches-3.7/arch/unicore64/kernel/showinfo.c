#include <linux/kernel.h>
#include <linux/elfcore.h>
#include <linux/bug.h>
#include <linux/sched.h>

#include <asm/uaccess.h>
#include <asm/setup_arch.h>

#include <arch/hwdef-cpu.h>
#include <arch/hwdef-cp0-sysctrl.h>

void __show_uc64_regs(struct pt_regs *regs)
{
	int i;

	if (regs == NULL)
		regs = task_pt_regs(current);

	pr_info("\nUniCore64 pt_regs at %lx:\n", (unsigned long)regs);
	pr_info(" ASR(value %lx):", regs->UC64_ASR);
	pr_cont(" %s Mode,",
			(regs->UC64_ASR & ASR_MODE_DEBUG) ? "DEBUG" :
			((regs->UC64_ASR & ASR_MODE_PRIV) ? "PRIV" : "USER"));
	pr_cont(" DebugExcp(%s)",
			(regs->UC64_ASR & ASR_D_BIT) ? "OFF" : "ON");
	pr_cont(" MPConsist(%s)\n",
			(regs->UC64_ASR & ASR_T_BIT) ? "ON" : "OFF");
	pr_info(" Intr PMF(%s) DEV(%s) OTM(%s) ITM(%s) LSU(%s) SMP(%s)\n",
			(regs->UC64_ASR & ASR_INTR_PFM) ? "OFF" : "ON",
			(regs->UC64_ASR & ASR_INTR_DEV) ? "OFF" : "ON",
			(regs->UC64_ASR & ASR_INTR_OTM) ? "OFF" : "ON",
			(regs->UC64_ASR & ASR_INTR_ITM) ? "OFF" : "ON",
			(regs->UC64_ASR & ASR_INTR_LSU) ? "OFF" : "ON",
			(regs->UC64_ASR & ASR_INTR_SMP) ? "OFF" : "ON");
	pr_info(" AFR(value %lx): %s%s%s%s\n", regs->UC64_AFR,
			(regs->UC64_AFR & AFR_S_BIT) ? "S" : "s",
			(regs->UC64_AFR & AFR_Z_BIT) ? "Z" : "z",
			(regs->UC64_AFR & AFR_C_BIT) ? "C" : "c",
			(regs->UC64_AFR & AFR_V_BIT) ? "V" : "v");

	for (i = 0; i < 28; i += 4)
		pr_info(" R%02d~R%02d: %16lx %16lx %16lx %16lx\n", i, i + 3,
			regs->uc64_regs[i], regs->uc64_regs[i + 1],
			regs->uc64_regs[i + 2], regs->uc64_regs[i + 3]);

	pr_info(" R28: %16lx USP: %016lx -- KSP: %016lx\n", regs->UC64_R28,
			regs->UC64_R29, regs->UC64_KSP);
	pr_info(" ULR: %016lx -- KLR: [<%016lx>] %pS\n", regs->UC64_R30,
			regs->UC64_KLR, (void *)regs->UC64_KLR);
	pr_info(" PC: [<%016lx>] %pS\n", regs->UC64_R31,
			(void *)regs->UC64_R31);
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
	pr_info("\nCP0 (System Control) Information:\n");
	pr_info(" CPUID:      %16lx\n", __read_cp_op(CP0_CPUID, 0));
	pr_info(" CACHE:      %16lx\n", __read_cp_op(CP0_CPUID, 1));
	pr_info(" CTRLREG:    %16lx\n", __read_cp(CP0_CTRLREG));
	pr_info(" TTB/ASID:   %16lx\n", __read_cp(CP0_TTB_ASID));
	pr_info(" ITRAPSTAT:  %16lx\n", __read_cp_op(CP0_TRAPSTAT, 0));
	pr_info(" DTRAPSTAT:  %16lx\n", __read_cp_op(CP0_TRAPSTAT, 1));
	pr_info(" ITRAPADDR:  %16lx\n", __read_cp_op(CP0_TRAPADDR, 1));
	pr_info(" DTRAPADDR:  %16lx\n", __read_cp_op(CP0_TRAPADDR, 0));

	pr_info(" MRAR_BASE:  %16lx %16lx %16lx %16lx\n",
			__read_cp_op(CP0_MRAR, 0),
			__read_cp_op(CP0_MRAR, 1),
			__read_cp_op(CP0_MRAR, 2),
			__read_cp_op(CP0_MRAR, 3));
	pr_info(" (Total 8):  %16lx %16lx %16lx %16lx\n",
			__read_cp_op(CP0_MRAR, 4),
			__read_cp_op(CP0_MRAR, 5),
			__read_cp_op(CP0_MRAR, 6),
			__read_cp_op(CP0_MRAR, 7));
	pr_info(" MRAR_MASK:  %16lx %16lx %16lx %16lx\n",
			__read_cp_op(CP0_MRAR, 8),
			__read_cp_op(CP0_MRAR, 9),
			__read_cp_op(CP0_MRAR, 10),
			__read_cp_op(CP0_MRAR, 11));
	pr_info(" (Total 8):  %16lx %16lx %16lx %16lx\n",
			__read_cp_op(CP0_MRAR, 12),
			__read_cp_op(CP0_MRAR, 13),
			__read_cp_op(CP0_MRAR, 14),
			__read_cp_op(CP0_MRAR, 15));

	pr_info(" VECBASE:    %16lx\n", __read_cp(CP0_VECBASE));
	pr_info(" INTR_TYPE:  %16lx\n", __read_cp_op(CP0_INTR, 0));
	pr_info(" INTR_PRIO:  %16lx\n", __read_cp_op(CP0_INTR, 7));
	pr_info(" ITM_CNTR:   %16lx\n", __read_cp_op(CP0_INTR, 9));
	pr_info(" ITM_MATCH:  %16lx\n", __read_cp_op(CP0_INTR, 10));

	pr_info(" R/W Margin: %16lx\n", __read_cp(CP0_RWMARGIN));
}

static void __dump_mem(unsigned long bottom, unsigned long top)
{
	pr_info("Dump memory from 0x%016lx to 0x%016lx:\n", bottom, top);
	print_hex_dump(KERN_INFO, " ", DUMP_PREFIX_ADDRESS, 16, 4,
			(void *)bottom, top - bottom, true);
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
	__show_uc64_regs(regs);
	__show_cp0_regs();
}

/**
 * show_stack() -
 * @tsk:
 * @sp:
 */
void show_stack(struct task_struct *tsk, unsigned long *sp)
{
	unsigned long addr;
	unsigned long stack_end;

	pr_info("\nCall Trace:\n");
	while (!kstack_end(sp)) {
		addr = *sp++;
		if (__kernel_text_address(addr))
			pr_info(" [<%016lx>] %pS\n", addr, (void *)addr);
	}

	stack_end = (unsigned long)current_thread_info();
	__dump_mem(stack_end, stack_end + THREAD_SIZE);
}
