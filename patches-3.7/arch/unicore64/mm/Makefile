ccflags-$(CONFIG_DEBUG_MCOUNT)	:= -pg
CFLAGS_REMOVE_fault.o		:= -pg
CFLAGS_REMOVE_mmu.o		:= -pg
CFLAGS_REMOVE_pgtable.o		:= -pg
CFLAGS_REMOVE_tlb.o		:= -pg

obj-y				:= fault.o ioremap.o init.o
obj-y				+= mmu.o pgtable.o tlb.o
obj-$(CONFIG_SWIOTLB)		+= dma-swiotlb.o
