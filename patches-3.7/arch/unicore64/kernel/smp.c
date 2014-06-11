#include <linux/init.h>
#include <linux/smp.h>
#include <linux/sched.h>
#include <linux/delay.h>
#include <linux/cpu.h>
#include <linux/interrupt.h>

#include <asm/pgtable.h>
#include <asm/tlbflush.h>
#include <arch/hwdef-cp0-sysctrl.h>

#define __ipi_disable()	\
	__write_uc64(__read_uc64(asr) | ASR_INTR_SMP, asr)
#define __ipi_clear()		\
	__write_cp(__read_cp(CP0_INTR) & ~CP0_INTR_SMP, CP0_INTR)

/* A collection of single bit ipi messages.  */
static struct {
	unsigned long bits ____cacheline_aligned;
} ipi_data[NR_CPUS] __cacheline_aligned;

enum ipi_message_type {
	IPI_RESCHEDULE,
	IPI_CALL_FUNC,
	IPI_CALL_FUNC_SINGLE,
	IPI_CPU_STOP,
};

unsigned int num_processors = 2;

/* Set when a secondary comes online.  */
static int smp_secondary_alive __devinitdata;

void __init smp_setup_processor_id(void)
{
	int i;

	for (i = 0; i < num_processors; i++)
		set_cpu_possible(i, true);
}

void __init smp_prepare_cpus(unsigned int max_cpus)
{
	int cpu;

	for_each_possible_cpu(cpu)
		set_cpu_present(cpu, true);
}

void __devinit smp_prepare_boot_cpu(void)
{
}

static void send_ipi(int cpu)
{
	switch (cpu) {
	case 0:
		__write_cp_op(0, CP0_INTR, 3);
		break;
	case 1:
		__write_cp_op(0, CP0_INTR, 4);
		break;
	case 2:
		__write_cp_op(0, CP0_INTR, 5);
		break;
	case 3:
		__write_cp_op(0, CP0_INTR, 6);
		break;
	default:
		printk(KERN_CRIT "Wrong core number\n");
	}
}

static void send_ipi_message(const struct cpumask *to_whom,
				enum ipi_message_type operation)
{
	int i;

	mb();
	for_each_cpu(i, to_whom)
		set_bit(operation, &ipi_data[i].bits);

	mb();
	for_each_cpu(i, to_whom)
		send_ipi(i);
}

/* This function handlers all IPIs. */
void ipi_handler(struct pt_regs *regs)
{
	struct pt_regs *old_regs = set_irq_regs(regs);
	int cpu = smp_processor_id();
	unsigned long *pending_ipis = &ipi_data[cpu].bits;
	unsigned long ops;

	/* IPI bits should be cleared before checking pending IPIs.*/
	__ipi_disable();
	__ipi_clear();

	/* Order interrupt and bit testing. */
	mb();
	while ((ops = xchg(pending_ipis, 0)) != 0) {
		/* Order bit clearing and data access. */
		mb();
		do {
			unsigned long which;

			which = ops & -ops;
			ops &= ~which;
			which = __ffs(which);

			switch (which) {
			case IPI_RESCHEDULE:
				scheduler_ipi();
				break;

			case IPI_CALL_FUNC:
				irq_enter();
				generic_smp_call_function_interrupt();
				irq_exit();
				break;

			case IPI_CALL_FUNC_SINGLE:
				irq_enter();
				generic_smp_call_function_single_interrupt();
				irq_exit();
				break;

			case IPI_CPU_STOP:
				__halt();

			default:
				printk(KERN_CRIT "Unknown IPI on CPU %d: %lu\n",
					cpu, which);
				break;
			}
		} while (ops);

		/* Order data access and bit testing. */
		mb();
	}

	set_irq_regs(old_regs);
}

void smp_send_reschedule(int cpu)
{
	send_ipi_message(cpumask_of(cpu), IPI_RESCHEDULE);
}

void arch_send_call_function_ipi_mask(const struct cpumask *mask)
{
	send_ipi_message(mask, IPI_CALL_FUNC);
}

void arch_send_call_function_single_ipi(int cpu)
{
	send_ipi_message(cpumask_of(cpu), IPI_CALL_FUNC_SINGLE);
}

void __init smp_cpus_done(unsigned int max_cpus)
{
	unsigned long bogosum = loops_per_jiffy * num_online_cpus();

	pr_info("SMP: Total of %d processors activated (%lu.%02lu BogoMIPS).\n",
		num_online_cpus(), bogosum / (500000/HZ),
		(bogosum / (5000/HZ)) % 100);
}

volatile unsigned long secondary_stack_start;

/*
 * CSR is not quite ready. Use a temporary reg 0xff6100000.
 */
#define CSR_R0	0xfffffffff6100000

static int __init smp_boot_one_cpu(unsigned int cpu, struct task_struct *idle)
{
	unsigned long timeout;

	smp_secondary_alive = 0;

	wmb();

	__asm__ __volatile__(
		"dmovl	r0, #" __stringify(CSR_R0) "\n"
		"ldd	r1, =secondary_stext\n"
		"stw	r1, [r0]\n"
		"movc	p0.c10, r0, #4");

	/* Wait one second for secondary to start up. */
	timeout = jiffies + 1 * HZ;
	while (time_before(jiffies, timeout)) {
		if (smp_secondary_alive == 1)
			goto alive;
		udelay(10);
		barrier();
	}

	/* We failed to boot the CPU.  */

	printk(KERN_ERR "SMP: Processor %d is stuck.\n", cpu);
	return -1;

 alive:
	return 0;
}

/*
 * Bring one cpu online.
 */
int __cpuinit __cpu_up(unsigned int cpu, struct task_struct *idle)
{
	/*
	 * We need to tell the secondary core where to find its stack.
	 */
	secondary_stack_start = (unsigned long) task_stack_page(idle)
			+ THREAD_SIZE - KSTK_PTREGS_GAP;
	mb();

	/*
	 * Now bring the CPU into our world.
	 */
	smp_boot_one_cpu(cpu, idle);

	return cpu_online(cpu) ? 0 : -1;
}

/*
 * Where secondaries begin a life of C.
 */
void __init secondary_start_kernel(void)
{
	unsigned int cpu = smp_processor_id();

	/* First 1G for direct-mapped area should be cleared. */
	swapper_pg_dir[0] = __pgd(0);
	atomic_inc(&init_mm.mm_count);
	current->active_mm = &init_mm;

	preempt_disable();

	setup_itimer();

	notify_cpu_starting(cpu);

	set_cpu_online(cpu, true);

	local_irq_enable();

	smp_secondary_alive = 1;

	cpu_idle();
}

void smp_send_stop(void)
{
	cpumask_t to_whom;
	cpumask_copy(&to_whom, cpu_possible_mask);
	cpumask_clear_cpu(smp_processor_id(), &to_whom);

	send_ipi_message(&to_whom, IPI_CPU_STOP);
}

static void ipi_flush_tlb_mm(void *x)
{
	__invalid_tlb();
}

void flush_tlb_mm(struct mm_struct *mm)
{
	preempt_disable();

	if (mm == current->active_mm)
		__invalid_tlb();

	if (smp_call_function(ipi_flush_tlb_mm, NULL, 1)) {
		printk(KERN_CRIT "flush_tlb_mm: timed out\n");
	}

	preempt_enable();
}

static void ipi_flush_tlb_page(void *x)
{
	/* flush the whole tlb currently. */
	__invalid_tlb();
}

void flush_tlb_page(struct vm_area_struct *vma, unsigned long addr)
{
	struct mm_struct *mm = vma->vm_mm;

	preempt_disable();

	if (mm == current->active_mm)
		__invalid_tlb();

	if (smp_call_function(ipi_flush_tlb_page, NULL, 1)) {
		printk(KERN_CRIT "flush_tlb_page: timed out\n");
	}

	preempt_enable();
}

void flush_tlb_range(struct vm_area_struct *vma, unsigned long start,
		unsigned long end)
{
	/* flush the whole user tlb.  */
	flush_tlb_mm(vma->vm_mm);
}
