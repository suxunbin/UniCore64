#ifndef __UNICORE64_ASM_SPINLOCK_H__
#define __UNICORE64_ASM_SPINLOCK_H__

#ifndef CONFIG_SMP
#error <asm/spinlock.h> is used when CONFIG_SMP disabled
#endif

#include <linux/spinlock_types.h>
#include <linux/stringify.h>

/* In order to support __lock_aligned in <asm-generic/bitops/atomic.h>,
   We need it here. */
#include <linux/linkage.h>

#include <asm/processor.h>
#include <asm/barrier.h>
#include <arch/asm-debug.h>

#define arch_spin_lock_flags(lock, flags) arch_spin_lock(lock)

static inline void arch_spin_lock(arch_spinlock_t *lock)
{
	u32 tmp;

	__asm__ __volatile__(
		"1:	llw		%0, [%1]\n"
		"	cmpsub.a	%0, #" __stringify(UNLOCK_TOKEN) "\n"
		"	bne		1b\n"
		"	mov		%0, #" __stringify(LOCK_TOKEN) "\n"
		"	scw		%0, [%1]\n"
		"	cmpsub.a	%0, #0\n"
		"	beq		1b"
		: "=&r" (tmp)
		: "r" (&lock->lock)
		: "cc", "memory");

	smp_mb();
}

static inline void arch_spin_unlock(arch_spinlock_t *lock)
{
	smp_mb();

	lock->lock = UNLOCK_TOKEN;
}

static inline int arch_spin_trylock(arch_spinlock_t *lock)
{
	u32 tmp;

	__asm__ __volatile__(
		"	llw		%0, [%1]\n"
		"	cmpsub.a	%0, #" __stringify(UNLOCK_TOKEN) "\n"
		"	cmovne		%0, #0\n"
		"	bne		1f\n"
		"	mov		%0, #" __stringify(LOCK_TOKEN) "\n"
		"	scw		%0, [%1]\n"
		"1:"
		: "=&r" (tmp)
		: "r" (&lock->lock)
		: "cc", "memory");

	if (tmp)
		smp_mb();

	return tmp;
}

static inline void arch_read_lock(arch_rwlock_t *rw)
{
	u32 tmp;

	__asm__ __volatile__(
		"1:	llw		%0, [%1]\n"
		"	cmpsub.a	%0, #" __stringify(UNLOCK_TOKEN) "\n"
		"	bsl		1b\n"
		"	add		%0, %0, #1\n"
		"	scw		%0, [%1]\n"
		"	cmpsub.a	%0, #0\n"
		"	beq		1b"
		: "=&r" (tmp)
		: "r" (&rw->lock)
		: "cc", "memory");

	smp_mb();
}

static inline void arch_read_unlock(arch_rwlock_t *rw)
{
	u32 tmp;

	smp_mb();

	__asm__ __volatile__(
		"1:	llw		%0, [%1]\n"
		"	sub		%0, %0, #1\n"
		"	scw		%0, [%1]\n"
		"	cmpsub.a	%0, #0\n"
		"	beq		1b"
		: "=&r" (tmp)
		: "r" (&rw->lock)
		: "cc", "memory");
}

static inline int arch_read_trylock(arch_rwlock_t *rw)
{
	/* FIXME */
	__asm__(
		"dmovl r0, 0xdead0006\n\t"
		"call uc64_debug_putx\n\t"
	);
	return 0;
}

static inline void arch_write_lock(arch_rwlock_t *rw)
{
	u32 tmp;

	__asm__ __volatile__(
		"1:	llw		%0, [%1]\n"
		"	cmpsub.a	%0, #" __stringify(UNLOCK_TOKEN) "\n"
		"	bne		1b\n"
		"	movl		%0, #" __stringify(WRLOCK_TOKEN) "\n"
		"	scw		%0, [%1]\n"
		"	cmpsub.a	%0, #0\n"
		"	beq		1b"
		: "=&r" (tmp)
		: "r" (&rw->lock)
		: "cc", "memory");

	smp_mb();
}

static inline void arch_write_unlock(arch_rwlock_t *rw)
{
	smp_mb();

	rw->lock = UNLOCK_TOKEN;
}

static inline int arch_write_trylock(arch_rwlock_t *rw)
{
	/* FIXME */
	__asm__(
		"dmovl r0, 0xdead0009\n\t"
		"call uc64_debug_putx\n\t"
	);
	return 0;
}

#define arch_read_lock_flags(lock, flags) arch_read_lock(lock)
#define arch_write_lock_flags(lock, flags) arch_write_lock(lock)
#define arch_spin_is_locked(x)			\
	({					\
		((x)->lock != UNLOCK_TOKEN);	\
	})
#define arch_spin_unlock_wait(lock) \
	do { while (arch_spin_is_locked(lock)) cpu_relax(); } while (0)

#endif /* __UNICORE64_ASM_SPINLOCK_H__ */
