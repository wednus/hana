Preparation
=
Make the connections between eSPI and Arduino
- 25 (eSPI) <-> RST (Arduino)
- p3v3 <-> VCC
- GND <-> GND
- 9 <-> MISO (D12)
- 10 <-> MOSI (D11)
- 11 <-> SCK (D13)

Arduino Programing
=
Use avrdude with the following options intact as the minimum:

    avrdude-hackiot -c linuxspi -p atmega328p -P /dev/spidev0.1

Flashing
-

    avrdude-hackiot -c linuxspi -p atmega328p -P /dev/spidev0.1 -U flash:w:demo/blink.hex:i

    avrdude-hackiot -c linuxspi -p atmega328p -P /dev/spidev0.1 -U flash:w:demo/fade.hex:i

Fuse Setting
-
[WARNNING] Changing fuse setting may brick your device unresponsive for ICSP commands.

    -U efuse:w:0x00:m
    -U hfuse:w:0x00:m
    -U lfuse:w:0x00:m
    -U lock:w:0x00:m
