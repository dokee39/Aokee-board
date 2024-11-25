#!/bin/sh
arm-none-eabi-objcopy -O binary build/src/make-release/src.elf build/src/make-release/src.bin
openocd -f interface/cmsis-dap.cfg -f target/stm32g4x.cfg -c "program build/src/make-release/src.bin 0x08000000 verify reset exit"
