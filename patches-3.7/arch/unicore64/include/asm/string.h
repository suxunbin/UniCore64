#ifndef __UNICORE64_ASM_STRING_H__
#define __UNICORE64_ASM_STRING_H__

#include <linux/types.h>

#define __HAVE_ARCH_MEMCPY
extern void *memcpy(void *, const void *, __kernel_size_t);

#define __HAVE_ARCH_MEMSET
extern void *memset(void *, int, __kernel_size_t);

#endif /* __UNICORE64_ASM_STRING_H__ */
