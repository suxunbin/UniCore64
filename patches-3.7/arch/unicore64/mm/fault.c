#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/ptrace.h>
#include <linux/uaccess.h>

#include <arch/hwdef-cp0-sysctrl.h>

static void __fixup_exception(struct pt_regs *regs)
{
	const struct exception_table_entry *fixup;

	fixup = search_exception_tables(GET_IP(regs));

	if (fixup)
		SET_IP(regs, fixup->fixup);
	else
		BUG();
}

static void __do_pagefault(unsigned long addr, struct pt_regs *regs)
{
	struct task_struct *tsk;
	struct mm_struct *mm;

	tsk = current;
	mm = tsk->mm;

	if (!mm)
		/* If we have no user context, we must not take the fault.. */
		__fixup_exception(regs);

	/* FIXME */
	BUG();
}

#define __itrap_stat()	__read_cp_op(CP0_TRAPSTAT, 0)
#define __dtrap_stat()	__read_cp_op(CP0_TRAPSTAT, 1)

struct __trap_info {
	void (*fn) (unsigned long addr, struct pt_regs *);
	const char *name;
};

static struct __trap_info __itrap_info[] = {
	{ NULL,			"0: no error"				},
	{ NULL,			"1: access debug-specific area"		},
	{ NULL,			"2: 2nd level pagetable non-exist"	},
	{ NULL,			"3: 3rd level pagetable non-exist"	},
	{ __do_pagefault,	"4: page non-exist"			},
	{ NULL,			"5: superpage non-exist"		},
	{ NULL,			"6: non-executable instruction"		},
	{ NULL,			"7: access US=0 page in user mode"	},
	{ NULL,			"8: memory access error"		},
	{ NULL,			"9: icache parity error"		},
	{ NULL,			"a: icache access error"		},
	{ NULL,			"b: illegal instruction"		},
	{ NULL,			"c: previlege instruction"		},
	{ NULL,			"d: eret instruction exception"		},
	{ NULL,			"e: unknown itrap fault"		},
	{ NULL,			"f: unknown itrap fault"		},
};

static struct __trap_info __dtrap_info[] = {
	{ NULL,			"0: no error"				},
	{ NULL,			"1: access debug-specific area"		},
	{ NULL,			"2: 2nd level pagetable non-exist"	},
	{ NULL,			"3: 3rd level pagetable non-exist"	},
	{ __do_pagefault,	"4: page non-exist"			},
	{ NULL,			"5: superpage non-exist"		},
	{ NULL,			"6: read unreadable address"		},
	{ NULL,			"7: write unwritable address"		},
	{ NULL,			"8: access US=0 page in user mode"	},
	{ NULL,			"9: unalignment access"			},
	{ NULL,			"a: memory access error"		},
	{ NULL,			"b: dcache parity error"		},
	{ NULL,			"c: dcache access error"		},
	{ NULL,			"d: divide zero"			},
	{ NULL,			"e: access cacheable area in atomic op"	},
	{ NULL,			"f: unknown dtrap fault"		},
};

void __do_itrap(unsigned long addr, struct pt_regs *regs)
{
	struct __trap_info *info = __itrap_info + __itrap_stat();

	if (info->fn) {
		info->fn(addr, regs);
		return;
	}

	pr_emerg("Unhandled ITRAP: %s at 0x%16lx\n",
	       info->name, addr);
	BUG();
}

void __do_dtrap(unsigned long addr, struct pt_regs *regs)
{
	struct __trap_info *info;
	int dtno;

	dtno = __dtrap_stat();
	if (dtno & CP0_TRAPSTAT_UNALIGN) {
		pr_err("Error: DTRAP occured with Un-Alignment Sticky!\n");
		dtno &= CP0_TRAPSTAT_SELECT;
	}

	info = __dtrap_info + dtno;
	if (info->fn) {
		info->fn(addr, regs);
		return;
	}

	pr_emerg("Unhandled DTRAP: %s at 0x%16lx\n",
	       info->name, addr);
	BUG();
}
