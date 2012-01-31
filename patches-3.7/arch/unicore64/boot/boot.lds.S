#include <arch/hwdef-memory.h>

OUTPUT_ARCH(unicore64)
ENTRY(_start)
SECTIONS
{
	. = UC64_PM_ZIMAGE_START;

	.text : {
		*(.start)
		*(.text)
		*(.rodata)
		*(.rodata.*)
	}

	. = ALIGN(8);

	/* ____bss_temp_handler: a trick to clear bss */
	. = UC64_PM_ZIMAGE_HEAP_END;
	__bss_start = UC64_PM_ZIMAGE_HEAP_END;
	.bss : { *(.bss) }
	_end = UC64_PM_ZIMAGE_HEAP_END + 0x100;

	/DISCARD/ : {
		/*
		 * Discard any r/w data -
		 * This produces a link error if we have any, which is
		 * required for PIC decompression.  Local data generates
		 * GOTOFF relocations, which prevents it being relocated
		 * independently of the text/got segments.
		 */
		*(.data)
	}
}
