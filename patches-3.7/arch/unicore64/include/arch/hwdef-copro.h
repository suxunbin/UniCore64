#ifndef __UNICORE64_ARCH_HWDEF_COPRO_H__
#define __UNICORE64_ARCH_HWDEF_COPRO_H__

/**
 * DOC: HWDEF_COPRO_H
 *
 * This file defines coprocessor names and their register names.
 */
#include <linux/stringify.h>

#define __read_cp_op(reg, op_no)					\
	({								\
		unsigned long __val;					\
		__asm__ __volatile__("movc	%0, " __stringify(reg)	\
				", #" __stringify(op_no)		\
		    : "=r" (__val));					\
		__val;							\
	})

#define __write_cp_op(reg_value, reg, op_no)				\
	({								\
		__asm__ __volatile__("movc	" __stringify(reg)	\
			", %0, #" __stringify(op_no)			\
		    : : "r" (reg_value));				\
	})

#define __read_cp(rn)		__read_cp_op(rn, 0)
#define __write_cp(v, rn)	__write_cp_op(v, rn, 0)

#endif /* __UNICORE64_ARCH_HWDEF_COPRO_H__ */
