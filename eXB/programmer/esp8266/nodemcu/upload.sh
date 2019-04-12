#!/bin/sh
#
# ESP8266 Programming using HackIoT Hana (v1.5)
# - Program ESP-1 and other ESP8266-based boards using a hat designed for eXB port
# - Sundew Shin - sundew@wednus.com
# - 1/14/2019
# - http://flat.wednus.com/forum

BAUD=57600
PROG_PIN=2      # GPIO27(mode)-ESP_GPIO0: 'out' && 0 => PROG | 'in' => RUN
RESET_PIN=25    # GPIO26(reset)-ESP_RST: ESP reset pin

#FW=./firmware     # use prebuilt images
FW=/workspace/libraries/Wednus/nodemcu/bin

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
  0x00000 $FW/0x00000.bin \
  0x10000 $FW/0x10000.bin \
  0x70000 $FW/0x70000-4mb.img


echo Resetting module...
gpio write $PROG_PIN 1 # set PROG mode
# trigger PROG->RUN
gpio write $RESET_PIN 0
sleep 1
gpio write $RESET_PIN 1
