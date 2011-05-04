#ifndef __ASM_UNICORE64_PROCESSOR_H__
#define __ASM_UNICORE64_PROCESSOR_H__

#ifdef __KERNEL__

struct thread_struct { };
#define INIT_THREAD		{ }

#define cpu_relax()		barrier()

#endif

#endif /* __ASM_UNICORE64_PROCESSOR_H__ */
