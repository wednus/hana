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
