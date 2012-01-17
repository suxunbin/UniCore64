#include <linux/init.h>
#include <linux/platform_device.h>

#include <arch/hwdef-puv3.h>
#include <arch/hwdef-irq.h>

static struct resource puv3_gpio_resources[] = {
	[0] = {
		.start	= PUV3_GPIO_BASE,
		.end	= PUV3_GPIO_BASE + PUV3_IOMEM_REGION,
		.flags	= IORESOURCE_MEM,
	},
};

static struct resource puv3_intc_resources[] = {
	[0] = {
		.start	= PUV3_INTC_BASE,
		.end	= PUV3_INTC_BASE + PUV3_IOMEM_REGION,
		.flags	= IORESOURCE_MEM,
	},
};

static struct resource puv3_ost_resources[] = {
	[0] = {
		.start	= PUV3_OST_BASE,
		.end	= PUV3_OST_BASE + PUV3_IOMEM_REGION,
		.flags	= IORESOURCE_MEM,
	},
	[1] = {
		.start	= IRQ_TIMER0,
		.flags	= IORESOURCE_IRQ,
	},
};

int __init puv3_core_init(void)
{
	/* APB-5 */
	platform_device_register_simple("PUV3-INTC", -1,
			puv3_intc_resources, ARRAY_SIZE(puv3_intc_resources));
	/* APB-6 */
	platform_device_register_simple("PUV3-GPIO", -1,
			puv3_gpio_resources, ARRAY_SIZE(puv3_gpio_resources));
	/* APB-8 */
	platform_device_register_simple("PUV3-OST", -1,
			puv3_ost_resources, ARRAY_SIZE(puv3_ost_resources));

	return 0;
}
postcore_initcall(puv3_core_init);
