ESP8266: NodeMCU Flashing
=

## Prerequisites

    pip install esptool
    git clone https://github.com/espressif/ESP8266_NONOS_SDK

## Build firmware

    cd nodemcu-firmware
    make

ref: https://medium.com/@cilliemalan/getting-started-on-nodemcu-with-your-own-firmware-cb2feffb067f


#### estool Options

- before no_reset
- after no_reset<br>
  Currently SBC's DTR connected to the AVR's reset, not ESP.
- no-stub<br>
  Not uploading 'stub loader' that manages flash operations, and only talk directly to the loader in ROM.
  Certain options will be disabled since not all options are implemented in every chip's ROM loader.


## Examples
#### Run in PROGRAM Mode

    esptool.py -p /dev/serial0 -b 57600 \
      --before no_reset --after no_reset --no-stub \
      flash_id

    esptool.py -p /dev/serial0 -b 57600 \
      --before no_reset --after no_reset --no-stub \
      write_flash --flash_freq 40m --flash_mode qio \
      0x0000 ./nodemcu-float.bin

    esptool.py -p /dev/serial0 -b 57600 \
      --before no_reset --after no_reset --no-stub \
      write_flash --flash_freq 40m --flash_mode qio \
      0x0000 boot_v1.7.bin \
      0x1000 user1.1024.new.2.bin \
      0x7E000 blank.bin


## LUA Basics

    file.remove("init.lua")

    if file.open("credentials.lua", "a+") then
      -- write 'foo bar' to the end of the file
      file.writeline('SSID = "blue"')
      file.writeline('PASSWORD = "Tjseb4fkd"')
      file.close()
    end

    l = file.list();
    for k,v in pairs(l) do
        print("name:"..k..", size:"..v)
    end
