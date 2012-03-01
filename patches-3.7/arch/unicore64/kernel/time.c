#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/errno.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/clockchips.h>

#include <arch/hwdef-cp0-sysctrl.h>

#define __itimer_read_counter()		__read_cp_op(CP0_INTR, 1)
#define __itimer_write_counter(cnt)	__write_cp_op(cnt, CP0_INTR, 1)

#define __itimer_irq_enable()					\
	__write_uc64(__read_uc64(asr) & ~ASR_INTR_ITM, asr)
#define __itimer_irq_disable()					\
	__write_uc64(__read_uc64(asr) | ASR_INTR_ITM, asr)
#define __itimer_irq_clear()					\
	__write_cp(__read_cp(CP0_INTR) & ~CP0_INTR_ITM, CP0_INTR)

#define MIN_COUNTER_DELTA			(2)

static cycle_t __itimer_read(struct clocksource *cs)
{
	return	__itimer_read_counter();
}

static int __itimer_set_next_event(unsigned long delta,
		struct clock_event_device *c)
{
	unsigned long next, count;

	__itimer_irq_enable();

	next = __itimer_read_counter() + delta;
	__itimer_write_counter(next);
	count = __itimer_read_counter();

	return (signed)(next - count) <= MIN_COUNTER_DELTA ? -ETIME : 0;
}

static void __itimer_set_mode(enum clock_event_mode mode,
		struct clock_event_device *c)
{
	switch (mode) {
	case CLOCK_EVT_MODE_ONESHOT:
		__itimer_irq_disable();
		__itimer_irq_clear();
		break;

	case CLOCK_EVT_MODE_UNUSED:
	case CLOCK_EVT_MODE_SHUTDOWN:
	case CLOCK_EVT_MODE_RESUME:
	case CLOCK_EVT_MODE_PERIODIC:
		break;
	}
}

static struct clock_event_device __itimer_ce = {
	.name		= "uc64-inner-timer-clock-event-device",
	.features	= CLOCK_EVT_FEAT_ONESHOT,
	.set_next_event	= __itimer_set_next_event,
	.set_mode	= __itimer_set_mode,
};

static struct clocksource __itimer_cs = {
	.name		= "uc64-inner-timer-clocksource",
	.read		= __itimer_read,
	.mask		= CLOCKSOURCE_MASK(64),
	.flags		= CLOCK_SOURCE_IS_CONTINUOUS,
};

void __itimer_irqhandler(void)
{
	/* Disarm the compare/match, signal the event. */
	__itimer_irq_disable();
	__itimer_irq_clear();

	__itimer_ce.event_handler(&__itimer_ce);
}

/**
 * time_init() -
 */
void __init time_init(void)
{
	/* hardware initialization */
	__itimer_irq_disable();
	__itimer_irq_clear();

	clockevents_calc_mult_shift(&__itimer_ce, CLOCK_TICK_RATE, 5);
	clocksource_register_hz(&__itimer_cs, CLOCK_TICK_RATE);
}
