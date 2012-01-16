/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#ifndef __UNICORE64_ARCH_BITFIELD_H__
#define __UNICORE64_ARCH_BITFIELD_H__

#include <linux/const.h>

#define BFSIZE(vbits)			(_AC(1, UL) << (vbits))
#define BFMASK(vmask, vshift)		(((BFSIZE(vmask)) - 1) << (vshift))
#define BFMASK_NOT(vmask, vshift)	(~BFMASK(vmask, vshift))

#define __BF(val, vmask, vshift)		\
		(((val) << (vshift)) & BFMASK(vmask, vshift))

/*
 * To define 64-bit addresses:
 *   HEX64(1f, ffffffff) means 0x1fffffffff
 */
#define HEX64(hi, lo)		_AC(0x ## hi ## lo, UL)

#endif /* __UNICORE64_ARCH_BITFIELD_H__ */
