#ifndef __UNICORE64_ASM_DELAY_H__
#define __UNICORE64_ASM_DELAY_H__

#include <linux/param.h>

extern void __delay(unsigned long loops);

/* If only we had a cycle counter... */
#define udelay(usecs)	__delay((usecs) * loops_per_jiffy * HZ / 1000000)

#endif /* __UNICORE64_ASM_DELAY_H__ */
