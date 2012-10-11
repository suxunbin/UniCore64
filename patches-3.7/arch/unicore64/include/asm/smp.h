#ifndef __UNICORE64_ASM_SMP_H__
#define __UNICORE64_ASM_SMP_H__

#ifndef CONFIG_SMP
# error "<asm/smp.h> included in non-SMP build"
#endif

#include <linux/threads.h>

#define raw_smp_processor_id() (current_thread_info()->cpu)

#endif /* __UNICORE64_ASM_SMP_H__ */
