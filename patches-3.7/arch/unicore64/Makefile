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

LDFLAGS_vmlinux		:= --no-undefined -X

OBJCOPYFLAGS		:= -O binary -R .note -R .note.gnu.build-id -R .comment -S

# Never use hard float in kernel
KBUILD_CFLAGS		+= -msoft-float

head-y			:= arch/unicore64/kernel/head.o
#head-y			+= arch/unicore64/kernel/init_task.o

core-y			+= arch/unicore64/kernel/
core-y			+= arch/unicore64/mm/

libs-y			+= arch/unicore64/lib/

all:	vmlinux

DOC_DIR			:= Documentation/DocBook
archdoc:
	$(Q)$(MAKE) $(build)=scripts build_docproc
	$(Q)$(MAKE) $(build)=$(DOC_DIR) DOCBOOKS=unicore64-kernel.xml pdfdocs

define archhelp
	echo  '  defconfig     - Use arch/$(ARCH)/configs/$(KBUILD_DEFCONFIG)'
	echo  '  archdoc       - Generate $(DOC_DIR)/unicore64-kernel.pdf'
endef
