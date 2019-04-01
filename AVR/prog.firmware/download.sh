#!/bin/sh
# This script download the AVR's flash contents into firmware.hex.

# backup existing
if [ -f firmware.hex ]; then
  mv firmware.hex firmware_backup_$(date +'%m%d%y_%H%M%S').hex
fi

avrdude -p m328p -P /dev/serial0 -c arduino -b 57600 -U flash:r:firmware.hex:r