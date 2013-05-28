#ifndef __UNICORE64_ASM_SMP_H__
#define __UNICORE64_ASM_SMP_H__

#ifndef CONFIG_SMP
# error "<asm/smp.h> included in non-SMP build"
#endif

#include <linux/threads.h>

#define raw_smp_processor_id() (current_thread_info()->cpu)

extern void arch_send_call_function_ipi_mask(const struct cpumask *mask);
extern void arch_send_call_function_single_ipi(int cpu);

extern void setup_itimer(void);

#endif /* __UNICORE64_ASM_SMP_H__ */
