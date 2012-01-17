# All targets during boot
targets		:= Image piggy.bin boot.lds boot.bin zImage unicore64-fpga.dtb

# Do not recognize built-in functions in uncompress.c
ccflags-y	:= -fno-builtin
# Use boot.lds as load-script
ldflags-y	:= -T $(obj)/boot.lds
# Only copy text segment from boot.bin to zImage
OBJCOPYFLAGS	:= -O binary -S

$(obj)/Image: vmlinux FORCE
	$(call if_changed,objcopy)
	@echo '  Kernel: $@ is ready'

# Compress Image Method
suffix_$(CONFIG_KERNEL_GZIP)	:= gzip
suffix_$(CONFIG_KERNEL_BZIP2)	:= bz2
suffix_$(CONFIG_KERNEL_LZO)	:= lzo
suffix_$(CONFIG_KERNEL_LZMA)	:= lzma

$(obj)/piggy.bin: $(obj)/Image FORCE
	$(call if_changed,$(suffix_y))

$(obj)/%.dtb: $(obj)/%.dts FORCE
	$(call if_changed,dtc)

$(obj)/boot-head.o: $(obj)/piggy.bin $(obj)/unicore64-fpga.dtb

BOOT_OBJS	:= $(srctree)/arch/unicore64/lib/memcpy.o
BOOT_OBJS	+= $(srctree)/arch/unicore64/lib/memset.o
BOOT_OBJS	+= $(srctree)/arch/unicore64/lib/wordcopy.o
BOOT_OBJS	+= $(srctree)/arch/unicore64/lib/debug.o
BOOT_OBJS	+= $(obj)/uncompress.o

$(obj)/boot.bin: $(obj)/boot.lds $(obj)/boot-head.o $(BOOT_OBJS) FORCE
	$(call if_changed,ld)
	@:

$(obj)/zImage: $(obj)/boot.bin FORCE
	$(call if_changed,objcopy)
	@echo '  Kernel: $@ is ready'
