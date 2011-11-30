#ifndef __UNICORE64_ASM_IRQFLAGS_H__
#define __UNICORE64_ASM_IRQFLAGS_H__

#include <arch/hwdef-cpu.h>

#define ARCH_IRQ_DISABLED	ASR_INTR_MASK
#define ARCH_IRQ_ENABLED	0x0

/**
 * arch_local_save_flags() - Save the current interrupt enable state.
 */
static inline unsigned long arch_local_save_flags(void)
{
	unsigned long temp;

	asm volatile("dmov %0, asr" : "=r" (temp));

	return temp & ASR_INTR_MASK;
}

/**
 * arch_local_irq_restore() - restore saved IRQ state
 * @flags:
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
