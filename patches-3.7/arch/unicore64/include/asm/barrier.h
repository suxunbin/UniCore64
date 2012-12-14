#ifndef __UNICORE64_ASM_BARRIER_H__
#define __UNICORE64_ASM_BARRIER_H__

#define mb()   __asm__ __volatile__ ("sync" : : : "memory")
#define rmb()  __asm__ __volatile__ ("sync" : : : "memory")
#define wmb()  __asm__ __volatile__ ("sync" : : : "memory")

#ifdef CONFIG_SMP
#define smp_mb()			mb()
#define smp_rmb()			rmb()
#define smp_wmb()			wmb()
#else
#define smp_mb()			barrier()
#define smp_rmb()			barrier()
#define smp_wmb()			barrier()
#endif

#define read_barrier_depends()		do { } while (0)
#define smp_read_barrier_depends()	do { } while (0)

#define set_mb(var, value)		do { var = value; smp_mb(); } while (0)

#endif /* __UNICORE64_ASM_BARRIER_H__ */
