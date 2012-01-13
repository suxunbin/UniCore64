#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/errno.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/clockchips.h>

#include <arch/hwdef-copro.h>
#include <arch/hwdef-irq.h>

#define INNER_TIMER_MATCHREG		p1.c0
#define INNER_TIMER_COUNTER		p1.c1
#define INNER_TIMER_STATUS		p1.c2
#define INNER_TIMER_IRQENABLE		p1.c3

#define uc64_inner_timer_irq_enable()					\
		write_cp(read_cp(INNER_TIMER_IRQENABLE) | 1,		\
				INNER_TIMER_IRQENABLE)

#define uc64_inner_timer_irq_disable()					\
		write_cp(read_cp(INNER_TIMER_IRQENABLE) & ~1,		\
				INNER_TIMER_IRQENABLE)

#define uc64_inner_timer_status_clear()					\
		write_cp(read_cp(INNER_TIMER_STATUS) & ~1,		\
				INNER_TIMER_STATUS)

#define MIN_COUNTER_DELTA			(2)

static cycle_t uc64_inner_timer_read(struct clocksource *cs)
{
	return	read_cp(INNER_TIMER_COUNTER);
}

static int uc64_inner_timer_set_next_event(unsigned long delta,
		struct clock_event_device *c)
{
	unsigned long next, count;

	uc64_inner_timer_irq_enable();

	next = read_cp(INNER_TIMER_COUNTER) + delta;
	write_cp(next, INNER_TIMER_MATCHREG);
	count = read_cp(INNER_TIMER_COUNTER);

	return (signed)(next - count) <= MIN_COUNTER_DELTA ? -ETIME : 0;
}

static void uc64_inner_timer_set_mode(enum clock_event_mode mode,
		struct clock_event_device *c)
{
	switch (mode) {
	case CLOCK_EVT_MODE_ONESHOT:
		uc64_inner_timer_irq_disable();
		uc64_inner_timer_status_clear();
		break;

	case CLOCK_EVT_MODE_UNUSED:
	case CLOCK_EVT_MODE_SHUTDOWN:
	case CLOCK_EVT_MODE_RESUME:
	case CLOCK_EVT_MODE_PERIODIC:
		break;
	}
}

static irqreturn_t uc64_inner_timer_irqhandler(int irq, void *dev_id)
{
	struct clock_event_device *c = dev_id;

	/* Disarm the compare/match, signal the event. */
	uc64_inner_timer_irq_disable();
	uc64_inner_timer_status_clear();
	c->event_handler(c);

	return IRQ_HANDLED;
}

static struct clock_event_device uc64_inner_timer_ce = {
	.name		= "uc64-inner-timer-clock-event-device",
	.features	= CLOCK_EVT_FEAT_ONESHOT,
	.set_next_event	= uc64_inner_timer_set_next_event,
	.set_mode	= uc64_inner_timer_set_mode,
};

static struct irqaction uc64_inner_timer_irq = {
	.name		= "uc64-inner-timer-irq",
	.flags		= IRQF_TIMER | IRQF_IRQPOLL,
	.handler	= uc64_inner_timer_irqhandler,
	.dev_id		= &uc64_inner_timer_ce,
};

static struct clocksource uc64_inner_timer_cs = {
	.name		= "uc64-inner-timer-clocksource",
	.read		= uc64_inner_timer_read,
	.mask		= CLOCKSOURCE_MASK(64),
	.flags		= CLOCK_SOURCE_IS_CONTINUOUS,
};

/**
 * time_init() -
 */
void __init time_init(void)
{
	/* hardware initialization */
	uc64_inner_timer_irq_disable();
	uc64_inner_timer_status_clear();

	clockevents_calc_mult_shift(&uc64_inner_timer_ce, CLOCK_TICK_RATE, 5);

	setup_irq(IRQ_TIMER0, &uc64_inner_timer_irq);

	clocksource_register_hz(&uc64_inner_timer_cs, CLOCK_TICK_RATE);
}
