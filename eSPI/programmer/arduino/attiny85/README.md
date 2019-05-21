ATTiny85 Programming
=

## Wiring
Make the connections between eSPI and Arduino
- p3v3 (eSPI)   <-> VCC (8) (Arduino)
- GND           <-> GND (4)
- 9             <-> MISO (6|PB1)
- 10            <-> MOSI (5|PB0)
- 11            <-> SCK (7|PB2)

## Flashing
Use avrdude with the following options intact as the minimum:

    avrdude -c linuxspi -p atmega328p -P /dev/spidev0.1

## Compile and Upload (.hex -> Arduino)
1. Create blink.ino as below as an example:

       void setup() {
         pinMode(3, OUTPUT);    // 0 ~ 5
       }
        
       void loop() {
         digitalWrite(3, HIGH);
         delay(1000);
         digitalWrite(3, LOW);
         delay(1000);
       }

2. Create Makefile

    BOARD_TAG = attiny85at8
    ALTERNATE_CORE = tiny
    #F_CPU = 1000000L
    ARDUINO_CORE_PATH = /usr/share/arduino/hardware/tiny/cores/tiny
    RESET_CMD = :
    HACKIOT_MAKEFILE = ./Makefile
    AVRDUDE_ARD_BAUDRATE = 57600
    AVRDUDE_ARD_PROGRAMMER = linuxspi
    ARDUINO_PORT = /dev/spidev0.1
    USER_LIB_PATH = /workspace/libraries
    ARDUINO_SKETCHBOOK = /usr/share/arduino
    include /usr/share/arduino/Arduino_hackiot.mk

3. Fuse Setting & Bootloader Upload

    avrdude -q -V -D -p attiny85 \
    -c linuxspi -b 57600 -P /dev/spidev0.1 \
    -e -U efuse:w:0xFF:m -U hfuse:w:0xD7:m -U lfuse:w:0xE2:m \
    -U flash:w:optiboot_attiny85.hex:i
    
4. Compile a sketch and upload

    make upload