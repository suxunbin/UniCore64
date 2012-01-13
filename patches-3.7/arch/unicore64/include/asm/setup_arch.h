#ifndef __UNICORE64_ASM_SETUP_ARCH_H__
#define __UNICORE64_ASM_SETUP_ARCH_H__

#include <linux/stringify.h>
#include <arch/hwdef-copro.h>

extern void setup_arch_cpuinfo(void);
extern void setup_arch_memory(void);

extern void paging_init(void);

#ifdef CONFIG_OF_EARLY_FLATTREE
extern void setup_arch_devtree(char *cmdline);
#else
#define setup_arch_devtree(s)		do { } while (0)
#endif /* CONFIG_OF_EARLY_FLATTREE */

#endif /* __UNICORE64_ASM_SETUP_ARCH_H__ */
