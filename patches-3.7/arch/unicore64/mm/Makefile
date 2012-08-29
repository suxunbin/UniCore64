ccflags-$(CONFIG_DEBUG_MCOUNT)	:= -pg

obj-y				:= fault.o ioremap.o init.o
obj-y				+= mmu.o pgtable.o tlb.o
obj-$(CONFIG_SWIOTLB)		+= dma-swiotlb.o
