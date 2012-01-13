#ifndef __UNICORE64_ARCH_HWDEF_COPRO_H__
#define __UNICORE64_ARCH_HWDEF_COPRO_H__

/**
 * DOC: HWDEF_COPRO_H
 *
 * This file defines coprocessor names and their register names.
 */
#include <arch/bitfield.h>

#define read_cp_off(reg_name, reg_offset)				\
	({								\
		unsigned long __val;					\
		asm("movc	%0, " __stringify(reg_name)		\
				", #" __stringify(reg_offset)		\
		    : "=r" (__val));					\
		__val;							\
	})

#define write_cp_off(reg_value, reg_name, reg_offset)			\
	({								\
		asm("movc	" __stringify(reg_name)			\
			", %0, #" __stringify(reg_offset)		\
		    : : "r" (reg_value));				\
	})

#define read_cp(rn)		read_cp_off(rn, 0)
#define write_cp(v, rn)		write_cp_off(v, rn, 0)

#endif /* __UNICORE64_ARCH_HWDEF_COPRO_H__ */
