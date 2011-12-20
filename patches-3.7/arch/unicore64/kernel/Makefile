#
# Makefile for the arch/unicore64/kernel.
#
obj-y			:= head.o entry.o
obj-y			+= init_task.o irq.o
obj-y			+= process.o ptrace.o
obj-y			+= setup.o sys.o
obj-y			+= time.o traps.o

obj-$(CONFIG_UNICORE64)	+= cpu-uc64.o

extra-y			:= vmlinux.lds
