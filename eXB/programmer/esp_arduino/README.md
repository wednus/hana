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
    FS_DIR = ./data             # default
    FLASH_DEF = 512K32          # create SPIFFS (check list_flash_defs)
    UPLOAD_PORT = /dev/serial0
    UPLOAD_SPEED = 19200
    ESP_ROOT = /workspace/libraries/esp8266com/esp8266
    include ./makeEspArduino.mk

#### Run Make

    make flash
You don't need 'make flash_fs' if FS_DIR has defined in Makefile.

## Monitoring
Open serial term (term.py) with baud rate 19200.

    ./term.py -b 19200
    
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
  - cause: unstable serial communication (stick to 19200; UPLOAD_SPEED = 19200)
  - symptoms: temporarily bricked from flashing
  - fix: try BBF below

#### Bootloader By Force (BBF)
Try resetting the ESP module using flash_id.sh or reset.sh in the ./tools folder while connecting:<br>(i.e. "Connecting........_____.....")

It can puth the ESP module in bootloader mode temporarily. (== stopping from resetting or unloacking from flashing)
