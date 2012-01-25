/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#ifndef __UNICORE64_ARCH_BITFIELD_H__
#define __UNICORE64_ARCH_BITFIELD_H__

#include <linux/const.h>

/*
 * __BP: power of 2 for _len
 * __BS: select bitpattern for bits of _len length from _sft bits
 * __BM: mask bitpattern for bits of _len length from _sft bits
 * __BF: field value is _val, for bits of _len length from _sft bits
 */
#define __BP(_len)		(_AC(1, UL) << (_len))
#define __BS(_len, _sft)	(((__BP(_len)) - 1) << (_sft))
#define __BM(_len, _sft)	(~__BS(_len, _sft))
#define __BF(_val, _len, _sft)	(((_val) << (_sft)) & __BS(_len, _sft))

/*
 * __BC: concatenate _hi and _lo to define 64-bit addresses:
 */
#define __BC(_hi, _lo)		_AC(0x ## _hi ## _lo, UL)

#endif /* __UNICORE64_ARCH_BITFIELD_H__ */
