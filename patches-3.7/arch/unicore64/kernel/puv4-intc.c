#include <linux/errno.h>
#include <linux/hardirq.h>
#include <linux/init.h>
#include <linux/io.h>
#include <linux/ioport.h>
#include <linux/irq.h>
#include <linux/platform_device.h>

#include <arch/puv4-irq.h>
#include <arch/puv4-regs-intc.h>

#define __puv4_intc_disable_all()	do {			\
			writel(0, INTC_ICMR);			\
			writel(0, INTC_ICLR);			\
			writel(1, INTC_ICCR);			\
		} while (0)

static void puv4_intc_mask_irq(struct irq_data *d)
{
	writel(readl(INTC_ICMR) & ~(1 << d->irq), INTC_ICMR);
}

static void puv4_intc_unmask_irq(struct irq_data *d)
{
	writel(readl(INTC_ICMR) | (1 << d->irq), INTC_ICMR);
}

/* We don't need to ACK IRQs on the PKUnity unless they're GPIOs */
static struct irq_chip puv4_intc_normal_chip = {
	.name		= "PUV4-INTC-NORMAL",
	.irq_ack	= puv4_intc_mask_irq,
	.irq_mask	= puv4_intc_mask_irq,
	.irq_unmask	= puv4_intc_unmask_irq,
};

static int __devinit puv4_intc_probe(struct platform_device *pdev)
{
	unsigned int irq;
	struct resource *res;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (res == NULL) {
		dev_err(&pdev->dev, "no memory resource defined\n");
		return -ENODEV;
	}

	res = request_mem_region(res->start, resource_size(res), pdev->name);
	if (res == NULL) {
		dev_err(&pdev->dev, "failed to request memory resource\n");
		return -EBUSY;
	}

	/* disable all IRQs */
	__puv4_intc_disable_all();

	for (irq = PUV4_IRQS_MIN; irq <= PUV4_IRQS_MAX; irq++) {
		irq_set_chip(irq, &puv4_intc_normal_chip);
		irq_set_handler(irq, handle_level_irq);
		irq_modify_status(irq, IRQ_NOREQUEST | IRQ_NOAUTOEN,
				IRQ_NOPROBE);
	}

	return 0;
}

static struct platform_driver puv4_intc_driver = {
	.driver		= {
		.name	= "PUV4-INTC",
	},
	.probe		= puv4_intc_probe,
};

static int __init puv4_intc_init(void)
{
	int ret = 0;

	ret = platform_driver_register(&puv4_intc_driver);
	if (ret) {
		pr_err("failed to register puv4_intc_driver\n");
	}

	return ret;
}
arch_initcall(puv4_intc_init);

/*
 * This function handles all puv4 hardware interrupts.
 */
void puv4_intc_handler(void)
{
	unsigned int irqs, irq;

	for (;;) {
		irqs = readl(INTC_ICIP) & readl(INTC_ICMR);
		if (irqs == 0)
			return;

		irq = ffs(irqs) - 1;
		irq_enter();
		generic_handle_irq(irq);
		irq_exit();
	}
}
