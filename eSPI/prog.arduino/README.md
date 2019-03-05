Preparation
=
Make the connections between eSPI and Arduino
- 25 (eSPI) <-> RST (Arduino)
- p3v3 <-> VCC
- GND <-> GND
- 9 <-> MISO (D12)
- 10 <-> MOSI (D11)
- 11 <-> SCK (D13)

Flashing
=
Use avrdude with the following options intact as the minimum:

    avrdude-hackiot -c linuxspi -p atmega328p -P /dev/spidev0.1

Testing:

    avrdude-hackiot -c linuxspi -p atmega328p -P /dev/spidev0.1 -v -v -v


### Download Flash to File
It creates 'firmware.hex' file.

    avrdude-hackiot -c linuxspi -p atmega328p -P /dev/spidev0.1flash:r:firmware.hex:r

### Upload

    avrdude-hackiot -c linuxspi -p atmega328p -P /dev/spidev0.1 -U flash:w:demo/blink.hex:i

    avrdude-hackiot -c linuxspi -p atmega328p -P /dev/spidev0.1 -U flash:w:demo/fade.hex:i

Fuse Settings
=
[WARNNING] Changing fuse setting may brick your device unresponsive for further ICSP commands.
If that happend, you may find this thread informative: https://www.avrfreaks.net/forum/tutsoft-recovering-locked-out-avr

Also, before fuse setting, double-verify your settings using AVR Studio or one of the online tools like this: http://www.engbedded.com/fusecalc/

    -U efuse:w:0x05:m
    -U hfuse:w:0xDA:m
    -U lfuse:w:0xFF:m
    -U lock:w:0x00:m
