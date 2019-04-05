#!/bin/sh
# This script downloads the specified firmware (*.bin) into AVR's flash memory.
# ATMega328p: Flash (32Kb), EEPROM (1Kb)

avrdude -p m328p -P /dev/serial0 -c arduino -b 57600 -U flash:w:$1

#avrdude -p m328p -P /dev/serial0 -c arduino -b 57600 -U flash:w:$1 \
#    -U eeprom:w:eeprom.hex \
#    -U efuse:w:0xFD:m \
#    -U hfuse:w:0xDA:m \
#    -U lfuse:w:0xFF:m