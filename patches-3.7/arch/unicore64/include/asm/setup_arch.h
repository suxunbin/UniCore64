#ifndef __UNICORE64_ASM_SETUP_ARCH_H__
#define __UNICORE64_ASM_SETUP_ARCH_H__

extern void setup_arch_cpuinfo(void);
extern void setup_arch_memory(void);

extern void paging_init(void);

#ifdef CONFIG_OF_EARLY_FLATTREE
extern void setup_arch_devtree(char *cmdline);
#else
#define setup_arch_devtree(s)		do { } while (0)
#endif /* CONFIG_OF_EARLY_FLATTREE */

extern char __vectors_table[];

extern void __show_uc64_regs(void);
extern void __show_cp0_regs(void);

#endif /* __UNICORE64_ASM_SETUP_ARCH_H__ */
