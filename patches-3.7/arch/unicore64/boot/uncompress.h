#ifndef __UNICORE64_BOOT_UNCOMPRESS_H__
#define __UNICORE64_BOOT_UNCOMPRESS_H__

#include <arch/asm-debug.h>

extern char input_data[];
extern char input_data_end[];

#define STATIC static
#define STATIC_RW_DATA	/* non-static please */
#define ARCH_HAVE_DECOMP_PUTS

/**
 * arch-dependent implementations
 */
#ifndef ARCH_HAVE_DECOMP_PUTS
#define arch_decomp_puts(p)
#else
#define arch_decomp_puts(p)	uc64_debug_puts(p, UC64_DEBUG_PUTS_MAXLEN)
#endif

#ifndef ARCH_HAVE_DECOMP_ERROR
#define arch_decomp_error()
#else
#define arch_decomp_error()	__halt()
#endif

#ifndef ARCH_HAVE_DECOMP_SETUP
#define arch_decomp_setup()
#endif

#endif /* __UNICORE64_BOOT_UNCOMPRESS_H__ */
