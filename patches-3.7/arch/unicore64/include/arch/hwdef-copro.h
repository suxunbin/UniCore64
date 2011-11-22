#ifndef __UNICORE64_ARCH_HWDEF_COPRO_H__
#define __UNICORE64_ARCH_HWDEF_COPRO_H__

/**
 * DOC: hwdef-copro.h
 *
 * This file defines coprocessor names and their register names.
 *
 *	cp0 is the control coprocesscor which helps the main processor
 *	with global control.
 *	CP0 CR0:	register that stores CPU information, Cache information
 *			and processor ID
 *	CP0 CR1:	control register of mmu and Cache
 *	CP0 CR2:	register for Translation Table Base and Address Space
 *			Identifier
 *	CP0 CR3:	register for status information of instruction
 *			and data abort
 *	CP0 CR4:	register for virtual address of data abort
 *	CP0 CR5:	register for TLB management
 *	CP0 CR6:	register for DCache management
 *	CP0 CR7:	register for ICache management
 *	CP0 CR8:	register for Memory Region Attribute Register
 *			configuration
 *	CP0 CR9:	register for interruption vector base
 *	CP0 CR10:	register for timer interrupt and interrupt information
 *			such as	number, type and priority
 *	CP0 CR11:	control register of Read/Write Margin
 */
#define CP0_CPUID		p0.c0
#define CP0_CTRLREG		p0.c1
#define CP0_TTB_ASID		p0.c2
#define CP0_ABORT_STAT		p0.c3
#define CP0_DABORT_VADDR	p0.c4
#define CP0_TLB			p0.c5
#define CP0_DCACHE		p0.c6
#define CP0_ICACHE		p0.c7
#define CP0_MRAR		p0.c8
#define CP0_INTR_VECBASE	p0.c9
#define CP0_INTR_STAT		p0.c10
#define CP0_RWM			p0.c11

#endif /* __UNICORE64_ARCH_HWDEF_COPRO_H__ */
