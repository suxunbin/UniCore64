#ifndef __UNICORE64_ASM_IRQFLAGS_H__
#define __UNICORE64_ASM_IRQFLAGS_H__

/**
 * DOC: IRQFLAGS_H
 * Code for interrupt control specific to PKUnity SoC and UniCore ISA.
 * Use the generic function for simple life.
 *
 * \\\\lt:programlisting\\\\gt:
 * -
 * arch_local_save_flags():		read interrupt enabled status
 * arch_local_irq_restore():	set interrupt enabled status
 * arch_local_irq_save():		get status and disable interrupts
 * arch_irqs_disabled_flags():	test flags
 * arch_local_irq_enable():		unconditionally enable interrupts
 * arch_local_irq_disable():	unconditionally disable interrupts
 * arch_irqs_disabled():		test hardware interrupt enable bit
 * -
 * \\\\lt:/programlisting\\\\gt:
 */

#include <arch/hwdef-cpu.h>

#define ARCH_IRQ_DISABLED	ASR_INTR_SELECT
#define ARCH_IRQ_ENABLED	0x0

/**
 * arch_local_save_flags() - Save the current interrupt enable state.
 *
 * Return codes:
 * Current CPU interrupt state.
 */
static inline unsigned long arch_local_save_flags(void)
{
	return __read_uc64(asr) & ASR_INTR_SELECT;
}

/**
 * arch_local_irq_restore() - restore saved IRQ state
 * @flags: CPU interrupt mask
 */
static inline void arch_local_irq_restore(unsigned long flags)
{
	__write_uc64((__read_uc64(asr) & ~ASR_INTR_SELECT) | (flags), asr);
}

#include <asm-generic/irqflags.h>

#endif /* __UNICORE64_ASM_IRQFLAGS_H__ */
