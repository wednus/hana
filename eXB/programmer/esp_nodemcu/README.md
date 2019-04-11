ESP8266 with NodeMCU
=

## Prerequisites

    git clone https://github.com/nodemcu/nodemcu-firmware.git

## Build NodeMCU
Put *.lua files in the './nodemcu-firmware/local/fs' folder

    cd nodemcu-firmware
    make

- [SPIFFS File System](https://github.com/nodemcu/nodemcu-firmware/blob/master/docs/spiffs.md)
- [Prepare custom build](https://medium.com/@cilliemalan/getting-started-on-nodemcu-with-your-own-firmware-cb2feffb067f)

#### Flashing
    ./upload.sh

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
      --before no_reset --after no_reset --no-stub write_flash \
      0x0000 ./nodemcu-float.bin

    esptool.py -p /dev/serial0 -b 57600 \
      --before no_reset --after no_reset --no-stub write_flash \
      0x0000 boot_v1.7.bin \
      0x1000 user1.1024.new.2.bin \
      0x7E000 blank.bin


## LUA Basics

    -- delete file --
    file.remove("init.lua")

    -- create file --
    if file.open("credentials.lua", "a+") then
      -- write 'foo bar' to the end of the file
      file.writeline('SSID = "blue"')
      file.writeline('PASSWORD = "Tjseb4fkd"')
      file.close()
    end

    -- Blink using timer alarm --
    -- use D4 (GPIO2)
    ledPin = 4
    -- set mode to output
    gpio.mode(ledPin,gpio.OUTPUT)
    ledState = 0
    -- timer loop
    tmr.create():alarm(1000, tmr.ALARM_AUTO, function()
      ledState = 1 - ledState;
      gpio.write(ledPin, ledState)
      print("LED:"..ledState)
    end)

    -- list files --
    l = file.list();
    for k,v in pairs(l) do
        print("name:"..k..", size:"..v)
    end
