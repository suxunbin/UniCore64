/**
 * DOC: TIME_C
 *
 * This file defines structures and functions that support itimer.
 */
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/errno.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/clockchips.h>

#include <arch/hwdef-cp0-sysctrl.h>

#define __itimer_read_counter()		__read_cp_op(CP0_INTR, 9)
#define __itimer_write_match(cnt)	__write_cp_op(cnt, CP0_INTR, 10)

#define __itimer_irq_enable()					\
	__write_uc64(__read_uc64(asr) & ~ASR_INTR_ITM, asr)
#define __itimer_irq_disable()					\
	__write_uc64(__read_uc64(asr) | ASR_INTR_ITM, asr)
#define __itimer_irq_clear()					\
	__write_cp(__read_cp(CP0_INTR) & ~CP0_INTR_ITM, CP0_INTR)

#define MIN_COUNTER_DELTA		(USEC_PER_SEC / CONFIG_HZ)
#define MAX_COUNTER_DELTA		(NSEC_PER_SEC / CONFIG_HZ)

/**
 * __itimer_read() - read itimer counter register
 * @cs:		pointer to clocksource __timer_cs
 *
 * Return code:
 * Return itimer counter
 */
static cycle_t __itimer_read(struct clocksource *cs)
{
	return	__itimer_read_counter();
}

/**
 * __itimer_set_next_event() - set itimer match register
 * @delta:	specify how many itimer cycles till next itimer irq
 * @c:		pointer to clock_event_device __itimer_ce
 *
 * Return code:
 * Return 0 on success, -ETIME when the event is in the past.
 *
 * This function sets itimer match register. When itimer counter equals
 * the value we set, we have next itimer irq.
 */
static int __itimer_set_next_event(unsigned long delta,
		struct clock_event_device *c)
{
	unsigned long next, count;

	next = __itimer_read_counter() + delta;
	__itimer_write_match(next);
	count = __itimer_read_counter();

	return (signed)(next - count) <= MIN_COUNTER_DELTA ? -ETIME : 0;
}

/**
 * __itimer_set_mode() - set the operating mode of itimer
 * @mode:	new mode
 * @c:		pointer to clock_event_device __itimer_ce
 */
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
	.rating		= 200,
	.read		= __itimer_read,
	.mask		= CLOCKSOURCE_MASK(64),
	.flags		= CLOCK_SOURCE_IS_CONTINUOUS,
};

/**
 * __itimer_irqhandler() - handler for itimer irq
 *
 * Clear corresponding bit of itimer irq in asr and call
 * architecture-independent handler.
 */
void __itimer_irqhandler(struct pt_regs *regs)
{
	struct pt_regs *old_regs = set_irq_regs(regs);
	irq_enter();

	/* Disarm the compare/match, signal the event. */
	__itimer_irq_disable();
	__itimer_irq_clear();

	__itimer_ce.event_handler(&__itimer_ce);

	irq_exit();
	set_irq_regs(old_regs);
}

/**
 * time_init() - initialize itimer
 *
 * Register clocksource and clock_event_device for itimer and configure
 * some parameters.
 */
void __init time_init(void)
{
	/* hardware initialization */
	__itimer_irq_disable();
	__itimer_irq_clear();

	clockevents_calc_mult_shift(&__itimer_ce, CLOCK_TICK_RATE, 5);

	__itimer_ce.max_delta_ns =
		clockevent_delta2ns(MAX_COUNTER_DELTA, &__itimer_ce);
	__itimer_ce.min_delta_ns =
		clockevent_delta2ns(MIN_COUNTER_DELTA, &__itimer_ce);

	clocksource_register_hz(&__itimer_cs, CLOCK_TICK_RATE);
	clockevents_register_device(&__itimer_ce);
}
