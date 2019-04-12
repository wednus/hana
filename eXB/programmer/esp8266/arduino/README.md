ESP8266/ESP32 w/ Makefile
=
This project demonstrates how to use Arduino environment for developing ESP8266 and ESP32 based modules.

## Prerequisite
- [Arduino core for ESP8266](https://github.com/esp8266/Arduino)
- [WiFiManager](https://github.com/tzapu/WiFiManager)

## How-to
#### Prepare Makefile
Edit Makefile

    BOARD = generic
    FLASH_DEF = 1M64
    UPLOAD_SPEED = 57600
    UPLOAD_PORT = /dev/serial0
    EXCLUDE_DIRS = ./firmware
    include /usr/share/arduino/makeEspArduino_hackiot.mk

#### Run Make

    make upload

## Monitoring
Open serial term (term.py) with baud rate 57600.

    ./term.py -b 57600
    
Reset the device and start monitoring any serial debug messages.

## Troubleshoot
#### Failure before flashing
- blue LED blinks rapidly
  - cause: invalid firmware loaded
  - symptoms: keep resetting; temporarily bricked from flashing
  - fix: try BBF below
  - Reference
      - [How To Unbrick ESP8266 (Blinking Blue Led)](https://blog.vinczejanos.info/2016/11/14/unbrick-esp8266-blinking-blue-led/)
#### Failure during flashing
- esptool.FatalError: Failed to write compressed data to flash after seq 0 (result was C100)
  - cause: unstable serial communication (stick to 57600; UPLOAD_SPEED = 57600)
  - symptoms: temporarily bricked from flashing
  - fix: try BBF below

#### Bootloader By Force (BBF)
Try resetting the ESP module using flash_id.sh or reset.sh in the ./tools folder while connecting:<br>(i.e. "Connecting........_____.....")

It can puth the ESP module in bootloader mode temporarily. (== stopping from resetting or unloacking from flashing)
