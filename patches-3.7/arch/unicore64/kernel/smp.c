#include <linux/init.h>
#include <linux/smp.h>

void __init smp_prepare_cpus(unsigned int max_cpus)
{
	/* FIXME */
	BUG();
}

void __devinit smp_prepare_boot_cpu(void)
{
	/* FIXME */
	BUG();
}

void smp_send_reschedule(int cpu)
{
	/* FIXME */
	BUG();
}

int smp_call_function(smp_call_func_t func, void *info, int wait)
{
	/* FIXME */
	BUG();
	return 0;
}

void smp_call_function_many(const struct cpumask *mask, smp_call_func_t func,
				void *info, bool wait)
{
	/* FIXME */
	BUG();
}

int smp_call_function_single(int cpuid, smp_call_func_t func, void *info,
				int wait)
{
	/* FIXME */
	BUG();
	return 0;
}

void __init smp_cpus_done(unsigned int max_cpus)
{
	/* FIXME */
	BUG();
}

int __cpuinit __cpu_up(unsigned int cpu, struct task_struct *tidle)
{
	/* FIXME */
	BUG();
	return 0;
}

void smp_send_stop(void)
{
	/* FIXME */
	BUG();
}
