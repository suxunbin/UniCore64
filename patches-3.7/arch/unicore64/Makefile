#
# arch/unicore64/Makefile
#
# This file is included by the global makefile so that you can add your own
# architecture-specific flags and dependencies.
#
# This file is subject to the terms and conditions of the GNU General Public
# License.  See the file "COPYING" in the main directory of this archive
# for more details.
#
# Copyright (C) 2011~2011 by Guan Xuetao
#
ifneq ($(SUBARCH),$(ARCH))
	ifeq ($(CROSS_COMPILE),)
		CROSS_COMPILE := $(call cc-cross-prefix, unicore64-linux-)
	endif
endif

# Provide the path to use for "make defconfig".
KBUILD_DEFCONFIG	:= $(ARCH)_defconfig

LDFLAGS_vmlinux		:= -p --no-undefined -X

OBJCOPYFLAGS		:= -O binary -R .note -R .note.gnu.build-id -R .comment -S

# Never use hard float in kernel
KBUILD_CFLAGS		+= -msoft-float

#head-y			:= arch/unicore64/kernel/head.o
#head-y			+= arch/unicore64/kernel/init_task.o

#core-y			+= arch/unicore64/kernel/
#core-y			+= arch/unicore64/mm/

#libs-y			+= arch/unicore64/lib/

ASM_GENERIC_HEADERS	:= auxvec.h
ASM_GENERIC_HEADERS	+= bug.h bugs.h
ASM_GENERIC_HEADERS	+= cache.h cacheflush.h
ASM_GENERIC_HEADERS	+= cmpxchg.h cmpxchg-local.h
ASM_GENERIC_HEADERS	+= cputime.h current.h
ASM_GENERIC_HEADERS	+= delay.h device.h div64.h dma.h
ASM_GENERIC_HEADERS	+= errno.h fcntl.h ftrace.h hardirq.h hw_irq.h
ASM_GENERIC_HEADERS	+= io.h ioctl.h ioctls.h ipcbuf.h
ASM_GENERIC_HEADERS	+= irq.h irq_regs.h irqflags.h
ASM_GENERIC_HEADERS	+= kmap_types.h linkage.h local.h
ASM_GENERIC_HEADERS	+= mman.h module.h msgbuf.h
ASM_GENERIC_HEADERS	+= param.h percpu.h poll.h posix_types.h resource.h
ASM_GENERIC_HEADERS	+= sections.h sembuf.h setup.h shmbuf.h shmparam.h
ASM_GENERIC_HEADERS	+= siginfo.h signal.h socket.h sockios.h
ASM_GENERIC_HEADERS	+= stat.h statfs.h string.h swab.h system.h
ASM_GENERIC_HEADERS	+= termbits.h termios.h topology.h types.h uaccess.h

archprepare:
	$(Q)$(foreach a, $(ASM_GENERIC_HEADERS),	\
		echo '#include <asm-generic/$a>'	\
			> $(srctree)/arch/unicore64/include/asm/$a; )

CLEAN_FILES		+= $(foreach a, $(ASM_GENERIC_HEADERS),		\
			$(srctree)/arch/unicore64/include/asm/$a )

all:	vmlinux

define archhelp
	echo  '  defconfig     - using arch/$(ARCH)/configs/$(KBUILD_DEFCONFIG)'
endef
