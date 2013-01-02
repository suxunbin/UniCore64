#include <linux/init.h>
#include <linux/platform_device.h>

#include <arch/puv4-iomem.h>
#include <arch/puv4-irq.h>

static struct resource puv4_gpio_resources[] = {
	[0] = {
		.start	= PUV4_GPIO_BASE,
		.end	= PUV4_GPIO_BASE + PUV4_IOMEM_REGION,
		.flags	= IORESOURCE_MEM,
	},
};

static struct resource puv4_intc_resources[] = {
	[0] = {
		.start	= PUV4_INTC_BASE,
		.end	= PUV4_INTC_BASE + PUV4_IOMEM_REGION,
		.flags	= IORESOURCE_MEM,
	},
};

static struct resource puv4_ost_resources[] = {
	[0] = {
		.start	= PUV4_OST_BASE,
		.end	= PUV4_OST_BASE + PUV4_IOMEM_REGION,
		.flags	= IORESOURCE_MEM,
	},
	[1] = {
		.start	= IRQ_TIMER0,
		.flags	= IORESOURCE_IRQ,
	},
};

static int __init puv4_core_init(void)
{
	/* APB-5 */
	platform_device_register_simple("PUV4-INTC", -1,
			puv4_intc_resources, ARRAY_SIZE(puv4_intc_resources));
	/* APB-6 */
	platform_device_register_simple("PUV4-GPIO", -1,
			puv4_gpio_resources, ARRAY_SIZE(puv4_gpio_resources));
	/* APB-8 */
	platform_device_register_simple("PUV4-OST", -1,
			puv4_ost_resources, ARRAY_SIZE(puv4_ost_resources));

	return 0;
}
postcore_initcall(puv4_core_init);
