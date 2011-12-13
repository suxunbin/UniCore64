lib-y			:= delay.o

GNU_LIBC_A		:= $(shell $(CC) $(KBUILD_CFLAGS) -print-file-name=libc.a)
GNU_LIBC_A_OBJS		:= memcpy.o memset.o wordcopy.o
lib-y			+= $(GNU_LIBC_A_OBJS)
$(addprefix $(obj)/, $(GNU_LIBC_A_OBJS)):
	$(Q)$(AR) p $(GNU_LIBC_A) $(notdir $@) > $@
