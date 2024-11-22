# Copyright (c) 2021, Niklas Hauser
#
# This file is part of the modm project.
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

profile?=release

# Toolchain configuration
CPPDEFINES += \
	-DSTM32G4

ifeq ($(profile),debug)
	CPPDEFINES += \
    	-DMODM_DEBUG_BUILD
endif

CCFLAGS := \
	-fdata-sections \
	-ffile-prefix-map=$(GCC_BASE)=. \
	-ffile-prefix-map=$(CURDIR)=. \
	-ffunction-sections \
	-finline-limit=10000 \
	-fno-builtin-printf \
	-fshort-wchar \
	-funsigned-bitfields \
	-funsigned-char \
	-fwrapv \
	-g3 \
	-gdwarf-3 \
	-W \
	-Wall \
	-Wdouble-promotion \
	-Wduplicated-cond \
	-Werror=format \
	-Werror=maybe-uninitialized \
	-Werror=overflow \
	-Werror=return-type \
	-Werror=sign-compare \
	-Wextra \
	-Wlogical-op \
	-Wno-redundant-decls \
	-Wpointer-arith \
	-Wundef

ifeq ($(profile),release)
	CCFLAGS += \
    	-Os
endif
ifeq ($(profile),debug)
	CCFLAGS += \
    	-fno-move-loop-invariants \
    	-fno-split-wide-types \
    	-fno-tree-loop-optimize \
    	-Og
endif

CFLAGS := \
	-std=gnu2x \
	-Wbad-function-cast \
	-Wimplicit \
	-Wredundant-decls \
	-Wstrict-prototypes


CXXFLAGS := \
	-fno-exceptions \
	-fno-rtti \
	-fno-unwind-tables \
	-fno-use-cxa-atexit \
	-fstrict-enums \
	-std=c++23 \
	-Wno-psabi \
	-Wno-volatile \
	-Woverloaded-virtual


ASFLAGS := \
	-g3 \
	-gdwarf-3


LINKFLAGS := \
	--specs=nano.specs \
	--specs=nosys.specs \
	-L$(CURDIR) \
	-nostartfiles \
	-Tmodm/link/linkerscript.ld \
	-Wl,--build-id=sha1 \
	-Wl,--fatal-warnings \
	-Wl,--gc-sections \
	-Wl,--no-warn-rwx-segment \
	-Wl,--no-wchar-size-warning \
	-Wl,--relax \
	-Wl,-Map,$(BUILDPATH)/$(MODM_PROJECT_NAME).map,--cref


ARCHFLAGS := \
	-mcpu=cortex-m4 \
	-mfloat-abi=hard \
	-mfpu=fpv4-sp-d16 \
	-mthumb



# ARCHFLAGS must be known for compiling *and* linking
CCFLAGS += $(ARCHFLAGS)
ASFLAGS += $(ARCHFLAGS)
LINKFLAGS += $(ARCHFLAGS)

# Include paths
CPPDEFINES += \
	-I$(MODM_PATH)/ext \
	-I$(MODM_PATH)/ext/cmsis/core \
	-I$(MODM_PATH)/ext/cmsis/device \
	-I$(MODM_PATH)/ext/gcc \
	-I$(MODM_PATH)/ext/tinyusb \
	-I$(MODM_PATH)/src
# Repo sources
MODM_OBJS += \
	$(BUILDPATH)/modm/ext/gcc/atomic.o \
	$(BUILDPATH)/modm/ext/gcc/cabi.o \
	$(BUILDPATH)/modm/ext/gcc/cxxabi.o \
	$(BUILDPATH)/modm/ext/gcc/new_delete.o \
	$(BUILDPATH)/modm/ext/printf/printf.o \
	$(BUILDPATH)/modm/ext/tinyusb/class/cdc/cdc_device.o \
	$(BUILDPATH)/modm/ext/tinyusb/common/tusb_fifo.o \
	$(BUILDPATH)/modm/ext/tinyusb/device/usbd.o \
	$(BUILDPATH)/modm/ext/tinyusb/device/usbd_control.o \
	$(BUILDPATH)/modm/ext/tinyusb/portable/st/stm32_fsdev/dcd_stm32_fsdev.o \
	$(BUILDPATH)/modm/ext/tinyusb/tusb.o \
	$(BUILDPATH)/modm/ext/tinyusb/tusb_descriptors.o \
	$(BUILDPATH)/modm/ext/tinyusb/tusb_port.o \
	$(BUILDPATH)/modm/src/modm/architecture/driver/atomic/flag.o \
	$(BUILDPATH)/modm/src/modm/container/smart_pointer.o \
	$(BUILDPATH)/modm/src/modm/io/iostream.o \
	$(BUILDPATH)/modm/src/modm/io/iostream_printf.o \
	$(BUILDPATH)/modm/src/modm/math/geometry/angle.o \
	$(BUILDPATH)/modm/src/modm/math/geometry/vector2.o \
	$(BUILDPATH)/modm/src/modm/math/utils/bit_operation.o \
	$(BUILDPATH)/modm/src/modm/math/utils/pc/operator.o \
	$(BUILDPATH)/modm/src/modm/platform/clock/rcc.o \
	$(BUILDPATH)/modm/src/modm/platform/clock/systick_timer.o \
	$(BUILDPATH)/modm/src/modm/platform/core/assert.o \
	$(BUILDPATH)/modm/src/modm/platform/core/delay.o \
	$(BUILDPATH)/modm/src/modm/platform/core/delay_ns.o \
	$(BUILDPATH)/modm/src/modm/platform/core/no_heap.o \
	$(BUILDPATH)/modm/src/modm/platform/core/reset_handler.o \
	$(BUILDPATH)/modm/src/modm/platform/core/startup.o \
	$(BUILDPATH)/modm/src/modm/platform/core/startup_platform.o \
	$(BUILDPATH)/modm/src/modm/platform/core/vectors.o \
	$(BUILDPATH)/modm/src/modm/platform/dma/dma.o \
	$(BUILDPATH)/modm/src/modm/platform/exti/exti.o \
	$(BUILDPATH)/modm/src/modm/platform/gpio/enable.o \
	$(BUILDPATH)/modm/src/modm/platform/i2c/i2c_master_1.o \
	$(BUILDPATH)/modm/src/modm/platform/spi/spi_master_1.o \
	$(BUILDPATH)/modm/src/modm/platform/spi/spi_master_3.o \
	$(BUILDPATH)/modm/src/modm/platform/uart/uart_1.o \
	$(BUILDPATH)/modm/src/modm/platform/uart/uart_2.o \
	$(BUILDPATH)/modm/src/modm/processing/fiber/context_arm_m.o \
	$(BUILDPATH)/modm/src/modm/processing/fiber/scheduler.o
# Include header dependencies files
-include $(MODM_OBJS:.o=.d)

# Custom build rules for repo sources
$(BUILDPATH)/modm/ext/printf/printf.o: $(OUTPATH)/modm/ext/printf/printf.c
	@$(call compile_c,$@,$<, -Wno-overflow \
		)
# Static library build rule
$(BUILDPATH)/modm/libmodm.a: $(MODM_OBJS)
	@echo "Archiving······" $(subst $(BUILDPATH_PREFIX),,$@)
	@$(AR) rc $@ $^
	@echo "Indexing·······" $(subst $(BUILDPATH_PREFIX),,$@)
	@$(RANLIB) $@

LIBS += $(BUILDPATH)/modm/libmodm.a

