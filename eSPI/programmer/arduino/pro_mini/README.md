## Wiring
Make the connections between eSPI and Arduino
- 25 (eSPI) <-> RST (Arduino)
- p3v3      <-> VCC
- GND       <-> GND
- 9         <-> MISO (D12)
- 10        <-> MOSI (D11)
- 11        <-> SCK (D13)

## Flashing
Use avrdude with the following options intact as the minimum:

    avrdude -c linuxspi -p atmega328p -P /dev/spidev0.1


## Compile and Upload (.hex -> Arduino)
1. Create blink.ino as below as an example:

       void setup() {
         pinMode(LED_BUILTIN, OUTPUT);
       }
        
       void loop() {
         digitalWrite(LED_BUILTIN, HIGH);
         delay(1000);
         digitalWrite(LED_BUILTIN, LOW);
         delay(1000);
       }

2. Create a Makefile in the same directory.

       BOARD_TAG = pro5v328        # <-- modify as needed
       RESET_CMD = :
       HACKIOT_MAKEFILE = ./Makefile
       AVRDUDE_ARD_PROGRAMMER = linuxspi
       AVRDUDE = /usr/bin/avrdude-hackiot
       ARDUINO_PORT = /dev/spidev0.1
       ARDUINO_LIBS =
       USER_LIB_PATH = /workspace/libraries
       ARDUINO_DIR = /usr/share/arduino
       include /usr/share/arduino/Arduino_hackiot.mk
    
3. Fuse Setting & Bootloader Upload

    avrdude -q -V -D -p m328p \
    -c linuxspi -b 57600 -P /dev/spidev0.1 \
    -e -U efuse:w:0xFD:m -U hfuse:w:0xDA:m -U lfuse:w:0xFF:m \
    -U flash:w:optiboot_atmega328.hex:i


4. Use Arduino-Makefile commands

       make upload

## Download (Arduino -> .hex)
It will download the Arduino's memory contents and create 'firmware.hex' file.

    avrdude -c linuxspi -p atmega328p -P /dev/spidev0.1 -U flash:r:firmware.hex:r

## Fuse Settings
[WARNNING] Changing fuse setting may brick your device unresponsive for further ICSP commands.
If that happend, you may find this thread informative: https://www.avrfreaks.net/forum/tutsoft-recovering-locked-out-avr

Also, before fuse setting, double-verify your settings using AVR Studio or one of the online tools like this: http://www.engbedded.com/fusecalc/

    -U efuse:w:0x05:m
    -U hfuse:w:0xDA:m
    -U lfuse:w:0xFF:m
    -U lock:w:0x00:m

## Troubleshoot
#### programmer type jtagice3_updi not found
- cause: included/specified makefile is invalid
- fix: check the syntax of included makefile