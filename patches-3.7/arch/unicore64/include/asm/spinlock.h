#ifndef __UNICORE64_ASM_SPINLOCK_H__
#define __UNICORE64_ASM_SPINLOCK_H__

#ifndef CONFIG_SMP
#error <asm/spinlock.h> is used when CONFIG_SMP disabled
#endif

#include <linux/spinlock_types.h>

/* In order to support __lock_aligned in <asm-generic/bitops/atomic.h>,
   We need it here. */
#include <linux/linkage.h>

#include <asm/processor.h>
#include <arch/asm-debug.h>

#define arch_spin_lock_flags(lock, flags) arch_spin_lock(lock)

static inline void arch_spin_lock(arch_spinlock_t *lock)
{
	/* FIXME */
	__asm__(
		"dmovl r0, 0xdead0001\n\t"
		"call uc64_debug_putx\n\t"
	);
}

static inline void arch_spin_unlock(arch_spinlock_t *lock)
{
	/* FIXME */
	__asm__(
		"dmovl r0, 0xdead0002\n\t"
		"call uc64_debug_putx\n\t"
	);
}

static inline int arch_spin_trylock(arch_spinlock_t *lock)
{
	/* FIXME */
	__asm__(
		"dmovl r0, 0xdead0003\n\t"
		"call uc64_debug_putx\n\t"
	);
	return 0;
}

static inline void arch_read_lock(arch_rwlock_t *rw)
{
	/* FIXME */
	__asm__(
		"dmovl r0, 0xdead0004\n\t"
		"call uc64_debug_putx\n\t"
	);
}

static inline void arch_read_unlock(arch_rwlock_t *rw)
{
	/* FIXME */
	__asm__(
		"dmovl r0, 0xdead0005\n\t"
		"call uc64_debug_putx\n\t"
	);
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
	/* FIXME */
	__asm__(
		"dmovl r0, 0xdead0007\n\t"
		"call uc64_debug_putx\n\t"
	);
}

static inline void arch_write_unlock(arch_rwlock_t *rw)
{
	/* FIXME */
	__asm__(
		"dmovl r0, 0xdead0008\n\t"
		"call uc64_debug_putx\n\t"
	);
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
		uc64_debug_putx(0xdead000a);	\
		((x)->lock != 0);		\
	})
#define arch_spin_unlock_wait(lock) \
	do { while (arch_spin_is_locked(lock)) cpu_relax(); } while (0)

#endif /* __UNICORE64_ASM_SPINLOCK_H__ */
