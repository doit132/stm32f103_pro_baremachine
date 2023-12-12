#!/bin/bash
xmake c
xmake f -c
xmake
cp build/*.hex $Desktop
arm-none-eabi-objdump -D build/STM32F103_Pro.elf > build/STM32F103_Pro.dis
