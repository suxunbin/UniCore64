#ifndef __UNICORE64_ASM_BITOPS_H__
#define __UNICORE64_ASM_BITOPS_H__

#define _ASM_GENERIC_BITOPS___FLS_H_
/*
 * __fls - find last (most-significant) set bit in a long word
 * @word: the word to search
 *
 * Undefined if no set bit exists, so code should check against 0 first.
 */
static inline unsigned long __fls(unsigned long word)
{
	/* FIXME: NOT implemented */
	return 0;
}

#define _ASM_GENERIC_BITOPS___FFS_H_
/*
 * __ffs - find first bit in word.
 * @word: The word to search
 *
 * Undefined if no bit exists, so code should check against 0 first.
 */
static inline unsigned long __ffs(unsigned long word)
{
	/* FIXME: NOT implemented */
	return 0;
}

#include <asm-generic/bitops.h>

#endif /* __UNICORE64_ASM_BITOPS_H__ */
