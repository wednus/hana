#!/bin/sh
#
# ESP8266 Programming using HackIoT Hana (v1.5)
# - Program ESP-1 and other ESP8266-based boards using a hat designed for eXB port
# - Sundew Shin - sundew@wednus.com
# - 1/14/2019
# - http://flat.wednus.com/forum
#
# set -x   # Uncomment to debug this shell script

BAUD=57600
PROG_PIN=2  # GPIO27(mode)-ESP_GPIO0: 'out' && 0 => PROG | 'in' => RUN
RESET_PIN=25 # GPIO26(reset)-ESP_RST: ESP reset pin

# init
gpio mode $RESET_PIN out
gpio mode $PROG_PIN out

# set prog mode
gpio write $PROG_PIN 0  # set PROG mode
# trigger RUN->PROG
gpio write $RESET_PIN 0
# give time to settle from busy running state
sleep 1
gpio write $RESET_PIN 1
#sleep 0.2

# test (optional)
./esptool.py -p /dev/serial0 -b $BAUD \
  --before no_reset --after no_reset --no-stub \
  flash_id
echo

# flashing firmware
./esptool.py -p /dev/serial0 -b $BAUD \
  --before no_reset --after no_reset --no-stub \
  write_flash --flash_mode qio \
  0x00000 AT_bin/boot_v1.5.bin \
  0x01000 AT_bin/512+512/user1.1024.new.2.bin \
  0x7e000 AT_bin/blank.bin \
  0xfe000 AT_bin/blank.bin
  
gpio write $PROG_PIN 1 # set RUN mode
# trigger PROG->RUN
gpio write $RESET_PIN 0
gpio write $RESET_PIN 1
