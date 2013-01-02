#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/io.h>

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

static struct resource puv4_ps2_resources[] = {
	[0] = {
		.start	= PUV4_PS2_BASE,
		.end	= PUV4_PS2_BASE + PUV4_IOMEM_REGION,
		.flags	= IORESOURCE_MEM,
	},
	[1] = {
		.start	= IRQ_PS2_KBD,
		.flags	= IORESOURCE_IRQ,
	},
};

static void puv4_ps2_init(void)
{
#ifdef CONFIG_ARCH_FPGA
	writeb(0x13, PS2_CNT);
#endif
}

static int __init puv4_core_init(void)
{
	puv4_ps2_init();

	/* APB-5 */
	platform_device_register_simple("PUV4-INTC", -1,
			puv4_intc_resources, ARRAY_SIZE(puv4_intc_resources));
	/* APB-6 */
	platform_device_register_simple("PUV4-GPIO", -1,
			puv4_gpio_resources, ARRAY_SIZE(puv4_gpio_resources));
	/* APB-8 */
	platform_device_register_simple("PUV4-OST", -1,
			puv4_ost_resources, ARRAY_SIZE(puv4_ost_resources));

	/* APB PS2 */
	platform_device_register_simple("PUV4-PS2", -1,
			puv4_ps2_resources, ARRAY_SIZE(puv4_ps2_resources));

	return 0;
}
postcore_initcall(puv4_core_init);
