#include <linux/linkage.h>

/**
 * __delay - delay routine
 * r0: loops per cycle
 */
ENTRY(__delay)
	dsub.a	r0, r0, #2
	bua	__delay
	return
ENDPROC(__delay)
