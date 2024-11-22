# Copyright (c) 2021, Niklas Hauser
#
# This file is part of the modm project.
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

C_PREFIX := arm-none-eabi-
ifeq ($(OS),Windows_NT)
	C_SUFFIX := .exe
else
endif

CC := $(C_PREFIX)gcc$(C_SUFFIX)
CXX := $(C_PREFIX)g++$(C_SUFFIX)
ASM := $(CC)

ifeq ($(C_SUFFIX),)
	AS := $(C_PREFIX)as
	AR := $(C_PREFIX)ar
	NM := $(C_PREFIX)nm
	RANLIB := $(C_PREFIX)ranlib
else
	AS := $(CXX)
	AR := $(C_PREFIX)gcc-ar$(C_SUFFIX)
	NM := $(C_PREFIX)gcc-nm$(C_SUFFIX)
	RANLIB := $(C_PREFIX)gcc-ranlib$(C_SUFFIX)
endif

OBJCOPY := $(C_PREFIX)objcopy
OBJDUMP := $(C_PREFIX)objdump
SIZE := $(C_PREFIX)size
STRIP := $(C_PREFIX)strip
DEBUGGER := $(C_PREFIX)gdb
CPPFILT := $(C_PREFIX)c++filt

GCC_BASE := $(dir $(realpath $(dir $(realpath $(shell which $(CC))))))
COMPILER_VERSION = $(shell $(CC) -dumpversion)
