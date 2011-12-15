lib-y			:= delay.o debug.o

GNU_LIBC_A		:= $(shell $(CC) $(KBUILD_CFLAGS) -print-file-name=libc.a)
GNU_LIBC_A_OBJS		:= memchr.o memcpy.o memmove.o memset.o wordcopy.o
lib-y			+= $(GNU_LIBC_A_OBJS)
$(addprefix $(obj)/, $(GNU_LIBC_A_OBJS)):
	$(Q)$(AR) p $(GNU_LIBC_A) $(notdir $@) > $@
