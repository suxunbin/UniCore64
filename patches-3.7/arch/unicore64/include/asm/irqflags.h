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

#define ARCH_IRQ_DISABLED	ASR_INTR_MASK
#define ARCH_IRQ_ENABLED	0x0

/**
 * arch_local_save_flags() - Save the current interrupt enable state.
 *
 * Return codes:
 * Current CPU interrupt state.
 */
static inline unsigned long arch_local_save_flags(void)
{
	unsigned long temp;

	asm volatile("dmov %0, asr" : "=r" (temp));

	return temp & ASR_INTR_MASK;
}

/**
 * arch_local_irq_restore() - restore saved IRQ state
 * @flags: CPU interrupt mask
 */
static inline void arch_local_irq_restore(unsigned long flags)
{
	unsigned long temp;

	asm volatile(
		"dmov	%0, asr\n"
		"dandn	%0, %0, %2\n"
		"dor	%0, %0, %1\n"
		"dmov	asr, %0"
		: "=&r" (temp)
		: "r" (flags), "i" (ASR_INTR_MASK));
}

#include <asm-generic/irqflags.h>

#endif /* __UNICORE64_ASM_IRQFLAGS_H__ */
