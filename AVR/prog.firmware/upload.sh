#!/bin/sh
# This script uploads the AVR's flash memory to the SBC as firmware.bin.

# backup existing
if [ -f firmware.bin ]; then
  mv firmware.bin __firmware_$(date +'%m%d%y_%H%M%S').bin
fi

avrdude -p m328p -P /dev/serial0 -c arduino -b 57600 -U flash:r:firmware.bin:r