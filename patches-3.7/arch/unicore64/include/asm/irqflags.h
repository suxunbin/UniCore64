#ifndef __ASM_UNICORE64_IRQFLAGS_H__
#define __ASM_UNICORE64_IRQFLAGS_H__

#ifdef __KERNEL__

/**
 * arch_local_save_flags() - Save the current interrupt enable state.
 */
static inline unsigned long arch_local_save_flags(void)
{
	/* FIXME */
	return 0;
}

/**
 * arch_local_irq_restore() - restore saved IRQ state
 * @flags:
 */
static inline void arch_local_irq_restore(unsigned long flags)
{
	/* FIXME */
}

#include <asm-generic/irqflags.h>

#endif /* __KERNEL__ */
#endif /* __ASM_UNICORE64_IRQFLAGS_H__ */
