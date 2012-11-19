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

static void __do_ipagefault(unsigned long address, struct pt_regs *regs)
{
	struct task_struct *tsk;
	struct mm_struct *mm;
	struct vm_area_struct *vma;
	unsigned long error_code;
	int fault;

	tsk = current;
	mm = tsk->mm;
	error_code = __read_cp_op(p0.c3, 0);

	if (!mm)
		/* If we have no user context, we must not take the fault.. */
		__fixup_exception(regs);

	vma = find_vma(mm, address);
	if (!vma)
		BUG();
	if (vma->vm_start <= address)
		goto good_area;
	if (!(vma->vm_flags & VM_GROWSDOWN))
		BUG();
	if (expand_stack(vma, address))
		BUG();

/*
 * Ok, we have a good vm_area for this memory access, so
 * we can handle it..
 */
good_area:
	if (error_code == 6) {
		if (!(vma->vm_flags & VM_EXEC))
			BUG();
	}

	/*
	 * If for any reason at all we couldn't handle the fault, make
	 * sure we exit gracefully rather than endlessly redo the fault.
	 */
	fault = handle_mm_fault(mm, vma, address, 0);
	if (unlikely(fault & VM_FAULT_ERROR))
		BUG();

	if (fault & VM_FAULT_MAJOR)
		tsk->maj_flt++;
	else
		tsk->min_flt++;

	return;
}

static void __do_dpagefault(unsigned long address, struct pt_regs *regs)
{
	struct task_struct *tsk;
	struct mm_struct *mm;
	struct vm_area_struct *vma;
	unsigned long error_code;
	int fault;

	tsk = current;
	mm = tsk->mm;
	error_code = __read_cp_op(p0.c3, 1);

	if (!mm)
		/* If we have no user context, we must not take the fault.. */
		__fixup_exception(regs);

	vma = find_vma(mm, address);
	if (!vma)
		BUG();
	if (vma->vm_start <= address)
		goto good_area;
	if (!(vma->vm_flags & VM_GROWSDOWN))
		BUG();
	if (expand_stack(vma, address))
		BUG();

/*
 * Ok, we have a good vm_area for this memory access, so
 * we can handle it..
 */
good_area:
	if (error_code == 7) {
		if (!(vma->vm_flags & VM_WRITE))
			BUG();
	}

	/*
	 * If for any reason at all we couldn't handle the fault, make
	 * sure we exit gracefully rather than endlessly redo the fault.
	 */
	fault = handle_mm_fault(mm, vma, address,
				(error_code == 7) ? FAULT_FLAG_WRITE : 0);
	if (unlikely(fault & VM_FAULT_ERROR))
		BUG();

	if (fault & VM_FAULT_MAJOR)
		tsk->maj_flt++;
	else
		tsk->min_flt++;

	return;
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
	{ __do_ipagefault,	"2: 2nd level pagetable non-exist"	},
	{ __do_ipagefault,	"3: 3rd level pagetable non-exist"	},
	{ __do_ipagefault,	"4: page non-exist"			},
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
	{ __do_dpagefault,	"2: 2nd level pagetable non-exist"	},
	{ __do_dpagefault,	"3: 3rd level pagetable non-exist"	},
	{ __do_dpagefault,	"4: page non-exist"			},
	{ NULL,			"5: superpage non-exist"		},
	{ NULL,			"6: read unreadable address"		},
	{ __do_dpagefault,	"7: write unwritable address"		},
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
	if (unlikely(dtno & CP0_TRAPSTAT_UNALIGN)) {
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
