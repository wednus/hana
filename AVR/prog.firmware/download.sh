#!/bin/sh
# This script download the AVR's flash contents into firmware.bin.

# backup existing
if [ -f firmware.bin ]; then
  mv firmware.bin firmware_backup_$(date +'%m%d%y_%H%M%S').bin
fi

avrdude -p m328p -P /dev/serial0 -c arduino -b 57600 -U flash:r:firmware.bin:r