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

	__bss_start = .;
	.bss : { *(.bss) }
	_end = .;

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
