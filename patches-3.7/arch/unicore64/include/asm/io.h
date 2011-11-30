#ifndef __UNICORE64_ASM_IO_H__
#define __UNICORE64_ASM_IO_H__

#include <asm-generic/io.h>

extern void iounmap(volatile void __iomem *addr);
extern void __iomem *ioremap(resource_size_t offset, unsigned long size);
extern void __iomem *ioremap_nocache(resource_size_t addr, unsigned long size);

#endif /* __UNICORE64_ASM_IO_H__ */
