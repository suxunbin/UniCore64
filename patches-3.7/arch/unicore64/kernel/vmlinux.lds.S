/**
 * DOC: VMLINUX_LDS_S
 * ld script to make UniCore64 Linux kernel
 */

#include <asm-generic/vmlinux.lds.h>
#include <asm/thread_info.h>
#include <asm/page.h>
#include <asm/cache.h>
#include <arch/hwdef-memory.h>

OUTPUT_ARCH(unicore64)
ENTRY(stext)

jiffies = jiffies_64;

SECTIONS
{
	. = PAGE_OFFSET + UC64_PM_KIMAGE_START;

	_text = .;
	__init_begin = .;
	HEAD_TEXT_SECTION
	INIT_TEXT_SECTION(PAGE_SIZE)
	INIT_DATA_SECTION(L1_CACHE_BYTES)
	PERCPU_SECTION(L1_CACHE_BYTES)
	. = ALIGN(PAGE_SIZE);
	__init_end = .;

	_stext = .;
	.text : {		/* Real text segment */
		TEXT_TEXT
		SCHED_TEXT
		LOCK_TEXT

		*(.fixup)
		*(.gnu.warning)
	}
	_etext = .;

	_sdata = .;
	RO_DATA_SECTION(PAGE_SIZE)
	RW_DATA_SECTION(L1_CACHE_BYTES, PAGE_SIZE, THREAD_SIZE)
	_edata = .;

	EXCEPTION_TABLE(L1_CACHE_BYTES)
	NOTES

	BSS_SECTION(L1_CACHE_BYTES, L1_CACHE_BYTES, L1_CACHE_BYTES)
	_end = .;

	STABS_DEBUG
	DWARF_DEBUG

	DISCARDS		/* Exit code and data */
}
