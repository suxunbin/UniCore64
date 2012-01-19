# All targets during boot
targets		:= Image piggy.bin boot.lds boot.bin zImage unicore64-fpga.dtb

# Do not recognize built-in functions in uncompress.c
ccflags-y	:= -fno-builtin
# Use boot.lds as load-script
ldflags-y	:= -T $(obj)/boot.lds
# Only copy text segment from boot.bin to zImage
OBJCOPYFLAGS	:= -O binary -S

# Step one: generate Image from vmlinux
$(obj)/Image: vmlinux FORCE
	$(call if_changed,objcopy)
	@echo '  Kernel: $@ is ready'

# Step two: compress Image to piggy.bin
suffix_$(CONFIG_KERNEL_GZIP)	:= gzip
suffix_$(CONFIG_KERNEL_BZIP2)	:= bzip2
suffix_$(CONFIG_KERNEL_LZO)	:= lzo
suffix_$(CONFIG_KERNEL_LZMA)	:= lzma

$(obj)/piggy.bin: $(obj)/Image FORCE
	$(call if_changed,$(suffix_y))

# Step three: generate boot.o, which includes piggy.bin and dtb file
$(obj)/%.dtb: $(obj)/%.dts FORCE
	$(call if_changed,dtc)

$(obj)/boot.o: $(obj)/piggy.bin $(obj)/unicore64-fpga.dtb

# Step four: generate boot.bin with special load-script
BOOT_OBJS	:= $(srctree)/arch/unicore64/lib/string-simple.o
BOOT_OBJS	+= $(srctree)/arch/unicore64/lib/debug.o
BOOT_OBJS	+= $(obj)/uncompress.o

$(obj)/boot.bin: $(obj)/boot.lds $(obj)/boot.o $(BOOT_OBJS) FORCE
	$(call if_changed,ld)
	@:

# Step five: generate zImage finally
$(obj)/zImage: $(obj)/boot.bin FORCE
	$(call if_changed,objcopy)
	@echo '  Kernel: $@ is ready'
