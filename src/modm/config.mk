# Copyright (c) 2021, 2023, Niklas Hauser
#
# This file is part of the modm project.
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

profile?=release
BUILDPATH_PREFIX := build/src/make-
BUILDPATH := $(BUILDPATH_PREFIX)$(profile)
OUTPATH := .
MODM_PROJECT_NAME := src
PYTHON3 := PYTHONPATH=$(MODM_PATH) python3

ELF_FILE := $(BUILDPATH)/$(MODM_PROJECT_NAME).elf
BIN_FILE := $(BUILDPATH)/$(MODM_PROJECT_NAME).bin
HEX_FILE := $(BUILDPATH)/$(MODM_PROJECT_NAME).hex
LSS_FILE := $(BUILDPATH)/$(MODM_PROJECT_NAME).lss
MAP_FILE := $(BUILDPATH)/$(MODM_PROJECT_NAME).map
UF2_FILE := $(BUILDPATH)/$(MODM_PROJECT_NAME).uf2
CLEAN_FILES += $(BUILDPATH)

# Device configuration
CONFIG_DEVICE_NAME := stm32g431kbt6
CONFIG_DEVICE_MEMORY := "[{'name': 'flash', 'access': 'rx', 'start': 134217728, 'size': 131072}, {'name': 'ccm', 'access': 'rwx', 'start': 268435456, 'size': 10240}, {'name': 'sram1', 'access': 'rwx', 'start': 536870912, 'size': 16384}, {'name': 'sram2', 'access': 'rwx', 'start': 536887296, 'size': 6144}]"
MODM_OPENOCD_CONFIGFILES += $(MODM_PATH)/openocd.cfg
MODM_JLINK_DEVICE = "stm32g431kb"
MODM_GDB_COMMANDS = -x $(MODM_PATH)/gdbinit -ex "dir $(GCC_BASE)" -ex "modm_setup_tui"
MODM_GDB_COMMANDS_OPENOCD = -x $(MODM_PATH)/gdbinit_openocd
MODM_GDB_COMMANDS_JLINK = -x $(MODM_PATH)/gdbinit_jlink
MODM_GDB_COMMANDS_BMP = -x $(MODM_PATH)/gdbinit_bmp
CONFIG_FLASH_OFFSET := 0
CONFIG_FLASH_ADDRESS := 0x8000000

include $(MODM_PATH)/compiler.mk

# Application sources
APP_SRC := $(APP_SRC:./%=%)
APP_SRC := $(filter-out $(MODM_PATH)/%,$(APP_SRC))
CPPDEFINES += -I.

# Application objects
APP_OBJS := $(addprefix $(BUILDPATH)/,$(APP_SRC))
APP_OBJS := $(APP_OBJS:.cpp=.o)
APP_OBJS := $(APP_OBJS:.cxx=.o)
APP_OBJS := $(APP_OBJS:.c++=.o)
APP_OBJS := $(APP_OBJS:.cc=.o)
APP_OBJS := $(APP_OBJS:.c=.o)
APP_OBJS := $(APP_OBJS:.sx=.o)
APP_OBJS := $(APP_OBJS:.s=.o)
APP_OBJS := $(APP_OBJS:.S=.o)
LIBRARIES := $(BUILDPATH)/modm/libmodm.a

# Application linking
.PRECIOUS: $(BUILDPATH)/%.elf
$(BUILDPATH)/%.elf: $(APP_OBJS) $(LIBRARIES) $(MODM_PATH)/link/linkerscript.ld
	@echo "Linking········" $@
	@$(CXX) -o $@ $(LINKFLAGS) $(filter %.o,$^) $(LIBPATH) \
		-Wl,--whole-archive -Wl,--start-group $(LIBS) -Wl,--end-group -Wl,--no-whole-archive

# Compiler invocations, -MMD is for header dependency tracking
compile_c = \
	echo "Compiling C····" $(subst $(BUILDPATH_PREFIX),,$1); \
	mkdir -p $(dir $1); \
	$(CC) -MMD -o $1 -c $(CFLAGS) $(CCFLAGS) $(CPPDEFINES) $3 $2

compile_cpp = \
	echo "Compiling C++··" $(subst $(BUILDPATH_PREFIX),,$1); \
	mkdir -p $(dir $1); \
	$(CXX) -MMD -o $1 -c $(CXXFLAGS) $(CCFLAGS) $(CPPDEFINES) $3 $2

compile_asm = \
	echo "Assembling·····" $(subst $(BUILDPATH_PREFIX),,$1); \
	mkdir -p $(dir $1); \
	$(CXX) -MMD -o $1 -c $(ASFLAGS) $(CPPDEFINES) $3 $2

# Build rules with relocation
.PRECIOUS: $(BUILDPATH)/%.o $(BUILDPATH)/%.a
$(BUILDPATH)/%.o : %.c
	@$(call compile_c,$@,$<,)
$(BUILDPATH)/%.o : %.cc
	@$(call compile_cpp,$@,$<,)
$(BUILDPATH)/%.o : %.cpp
	@$(call compile_cpp,$@,$<,)
$(BUILDPATH)/%.o : %.cxx
	@$(call compile_cpp,$@,$<,)
$(BUILDPATH)/%.o : %.c++
	@$(call compile_cpp,$@,$<,)
$(BUILDPATH)/%.o : %.sx
	@$(call compile_asm,$@,$<,)
$(BUILDPATH)/%.o : %.s
	@$(call compile_asm,$@,$<,)
$(BUILDPATH)/%.o : %.S
	@$(call compile_asm,$@,$<,)

.PRECIOUS: $(BUILDPATH)/%.bin
$(BUILDPATH)/%.bin: $(BUILDPATH)/%.elf
	@echo "Binary File····" $@
	@$(OBJCOPY) -O binary $< $@

.PRECIOUS: $(BUILDPATH)/%.hex
$(BUILDPATH)/%.hex: $(BUILDPATH)/%.elf
	@echo "Hex File·······" $@
	@$(OBJCOPY) -O ihex $< $@

.PRECIOUS: $(BUILDPATH)/%.lss
$(BUILDPATH)/%.lss: $(BUILDPATH)/%.elf
	@echo "Listing········" $@
	@$(OBJDUMP) -x -S -l -w $< > $@









