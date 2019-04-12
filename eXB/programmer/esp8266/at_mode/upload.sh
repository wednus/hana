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
FW=/workspace/libraries/Wednus/esp_at

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

# flashing firmware
./esptool.py -p /dev/serial0 -b $BAUD \
  --before no_reset --after no_reset --no-stub write_flash \
  0x00000 $FW/boot_v1.5.bin \
  0x01000 $FW/512+512/user1.1024.new.2.bin \
  0x7e000 $FW/blank.bin \
  0xfe000 $FW/blank.bin

#  0x00000 $FW/AI-Tinker_v1.3/at_fw.bin
  
echo Resetting module...
gpio write $PROG_PIN 1 # set RUN mode
# trigger PROG->RUN
gpio write $RESET_PIN 0
sleep 1
gpio write $RESET_PIN 1
