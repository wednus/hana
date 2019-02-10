#!/bin/sh
#
# ESP8266 Programming using HackIoT Hana (v1.5)
# - Program ESP-1 and other ESP8266-based boards using a hat designed for EXT_COMM slot
# - Sundew Shin - sundew@wednus.com
# - 1/14/2019
# - http://flat.wednus.com/forum
#
# set -x   # Uncomment to debug this shell script

# prep
make upload     # upload serial pass-through sketch (SBC <-> AVR <-> EXP_COMM)
gpio mode 2 out # GPIO27(mode): 'out' && 0 => PROG | 'in' => RUN
gpio mode 7 out # GPIO4(reset): ESP reset pin
gpio write 2 0  # set PROG mode
gpio write 7 1  # reset pull-up
# trigger RUN->PROG
gpio write 7 0
gpio write 7 1

# test (optional)
./esptool.py -p /dev/serial0 -b 19200 \
  --before no_reset --after no_reset --no-stub \
  flash_id
echo

# flashing firmware
./esptool.py -p /dev/serial0 -b 19200 \
  --before no_reset --after no_reset --no-stub \
  write_flash --flash_freq 40m --flash_mode qio 0x0000 \
  nodemcu-float.bin

gpio mode 2 in  # set RUN mode
# trigger PROG->RUN
gpio write 7 0
gpio write 7 1
