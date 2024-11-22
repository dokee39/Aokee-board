# Copyright (c) 2021, 2023, Niklas Hauser
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice, this
#    list of conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

MODM_PATH := modm
APP_SRC := $(shell find . -type f \( -name '*.c' -o -iname '*.s' -o -name '*.sx' \
			-o -name '*.cpp' -o -name '*.cxx' -o -name '*.c++' -o -name '*.cc' \) )

include $(MODM_PATH)/config.mk
include $(MODM_PATH)/repo.mk

.DEFAULT_GOAL := size

.PHONY: library listing bin hex
library: $(LIBRARIES)
listing: $(LSS_FILE)
bin: $(BIN_FILE)
hex: $(HEX_FILE)

.PHONY: symbols
symbols:
	@echo "Symbols········" $(ELF_FILE)
	@$(NM) -S -C --size-sort -td $(ELF_FILE)

.PHONY:  build
build: $(ELF_FILE)

.PHONY: clean
clean:
	@$(foreach file,$(CLEAN_FILES),echo "Removing·······" $(file);)
	@rm -rf $(CLEAN_FILES)

.PHONY: size
size: build
	@echo "Memory usage···" $(ELF_FILE)
	@$(PYTHON3) -m modm_tools.size $(ELF_FILE) $(CONFIG_DEVICE_MEMORY)

.PHONY: uf2
uf2: build
	@echo "UF2 File·······" $(UF2_FILE)
	@$(PYTHON3) -m modm_tools.elf2uf2 $(ELF_FILE) -o $(UF2_FILE) \
			--target $(CONFIG_DEVICE_NAME) \
			--range 0x8000000:0x8020000:CONTENTS \
			--range 0x10000000:0x10002800:NO_CONTENTS \
			--range 0x20000000:0x20004000:NO_CONTENTS \
			--range 0x20004000:0x20005800:NO_CONTENTS

port?=auto
.PHONY: program
program: build
	@$(PYTHON3) -m modm_tools.openocd $(ELF_FILE) \
			$(addprefix -f ,$(MODM_OPENOCD_CONFIGFILES))

.PHONY: program-bmp
program-bmp: build
	@$(PYTHON3) -m modm_tools.bmp -p $(port) $(ELF_FILE)

.PHONY: program-jlink
program-jlink: build
	@$(PYTHON3) -m modm_tools.jlink -device $(MODM_JLINK_DEVICE) $(ELF_FILE)

delay?=5
CONFIG_FLASH_ADDRESS?=0x08000000
.PHONY: program-dfu
program-dfu: bin
	@dfu-util -v -E$(delay) -R -i 0 -a 0 -s $(CONFIG_FLASH_ADDRESS):leave -D $(BIN_FILE)


.PHONY: reset
reset:
	@$(PYTHON3) -m modm_tools.openocd --reset \
			$(addprefix -f ,$(MODM_OPENOCD_CONFIGFILES))

.PHONY: reset-bmp
reset-bmp:
	@$(PYTHON3) -m modm_tools.bmp -p $(port) --reset

.PHONY: reset-jlink
reset-jlink:
	@$(PYTHON3) -m modm_tools.jlink -device $(MODM_JLINK_DEVICE) --reset

ui?=tui
.PHONY: debug
debug: build
	@$(PYTHON3) -m modm_tools.gdb $(MODM_GDB_COMMANDS) \
			$(MODM_GDB_COMMANDS_OPENOCD) --elf $(ELF_FILE) --ui=$(ui) \
			openocd $(addprefix -f ,$(MODM_OPENOCD_CONFIGFILES))

.PHONY: debug-bmp
debug-bmp: build
	@$(PYTHON3) -m modm_tools.gdb $(MODM_GDB_COMMANDS) \
			$(MODM_GDB_COMMANDS_BMP) --elf $(ELF_FILE) --ui=$(ui) \
			bmp -p $(port)

.PHONY: debug-jlink
debug-jlink: build
	@$(PYTHON3) -m modm_tools.gdb $(MODM_GDB_COMMANDS) \
			$(MODM_GDB_COMMANDS_JLINK) --elf $(ELF_FILE) --ui=$(ui) \
			jlink -device $(MODM_JLINK_DEVICE)

coredump?=coredump.txt
.PHONY: debug-coredump
debug-coredump: build
	@$(PYTHON3) -m modm_tools.gdb $(MODM_GDB_COMMANDS) \
			--elf $(ELF_FILE) --ui=$(ui) \
			crashdebug --dump $(coredump)

.PHONY: coredump
coredump:
	@$(PYTHON3) -m modm_tools.gdb $(MODM_GDB_COMMANDS) \
			-ex "modm_coredump" -ex "modm_build_id" -ex "quit" \
			openocd $(addprefix -f ,$(MODM_OPENOCD_CONFIGFILES))

.PHONY: coredump-bmp
coredump-bmp:
	@$(PYTHON3) -m modm_tools.gdb $(MODM_GDB_COMMANDS) \
			-ex "modm_coredump" -ex "modm_build_id" -ex "quit" \
			bmp -p $(port)

.PHONY: coredump-jlink
coredump-jlink:
	@$(PYTHON3) -m modm_tools.gdb $(MODM_GDB_COMMANDS) \
			-ex "modm_coredump" -ex "modm_build_id" -ex "quit" \
			jlink -device $(MODM_JLINK_DEVICE)

fcpu?=0
.PHONY: log-itm
log-itm:
	@$(PYTHON3) -m modm_tools.itm openocd -f $(MODM_PATH)/openocd.cfg --fcpu $(fcpu)

.PHONY: log-itm-jlink
log-itm-jlink:
	@$(PYTHON3) -m modm_tools.itm jlink -device $(MODM_JLINK_DEVICE)

channel?=0
.PHONY: log-rtt
log-rtt:
	@$(PYTHON3) -m modm_tools.rtt --channel $(channel) openocd -f $(MODM_PATH)/openocd.cfg

.PHONY: log-rtt-jlink
log-rtt-jlink:
	@$(PYTHON3) -m modm_tools.rtt --channel $(channel) jlink -device $(MODM_JLINK_DEVICE)
