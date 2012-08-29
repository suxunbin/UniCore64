#
# Makefile for the arch/unicore64/kernel.
#

# Handling MCOUNT situation
ccflags-$(CONFIG_DEBUG_MCOUNT)	:= -pg
CFLAGS_REMOVE_early_printk.o	:= -pg
CFLAGS_REMOVE_time.o		:= -pg

obj-y			:= head.o entry.o switch_to.o
obj-y			+= irq.o
obj-y			+= process.o ptrace.o
obj-y			+= setup.o showinfo.o sys.o
obj-y			+= time.o traps.o

obj-$(CONFIG_UNICORE64)		+= cpu-uc64.o
obj-$(CONFIG_OF_EARLY_FLATTREE)	+= devtree.o
obj-$(CONFIG_EARLY_PRINTK)	+= early_printk.o
obj-$(CONFIG_ARCH_PUV3)		+= puv3-core.o puv3-intc.o

extra-y			:= vmlinux.lds
