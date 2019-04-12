## ESP8266 AT Firmware
This uploader script can be used to unbrick modules.

#### Usage

    ./upload.sh

#### Test
1. Burn main.ino in ./firmwre.115200 to AVR
2. Open serial terminal i.e, './term.py -b 115200'
3. Reset the module using './tools/reset.sh'

#### References
[ESP8266 AT-Command firmware](https://www.electrodragon.com/w/ESP8266_AT-Command_firmware)