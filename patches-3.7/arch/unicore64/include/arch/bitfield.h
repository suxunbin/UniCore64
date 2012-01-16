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
 * __BM: mask for bits of _len length from _sft bits
 * __BS: select mask for bits of _len length from _sft bits
 * __BF: field value is _val, for bits of _len length from _sft bits
 */
#define __BP(_len)		(_AC(1, UL) << (_len))
#define __BM(_len, _sft)	(((__BP(_len)) - 1) << (_sft))
#define __BS(_len, _sft)	(~__BM(_len, _sft))
#define __BF(_val, _len, _sft)	(((_val) << (_sft)) & __BM(_len, _sft))

/*
 * To define 64-bit addresses:
 *   HEX64(1f, ffffffff) means 0x1fffffffff
 */
#define HEX64(hi, lo)		_AC(0x ## hi ## lo, UL)

#endif /* __UNICORE64_ARCH_BITFIELD_H__ */
