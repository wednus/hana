Examples for HackIoT Hana SDK
=============================
This repository contains the latest example code and sub-projects for HackIoT Hana's SDK.

Resources
---------
- [HackIoT Hana](http://flat.wednus.com/built-for-flat) | [flat, docker for SBCs](http://flat.wednus.com) 
- [Youtube Tutorials](https://www.youtube.com/playlist?list=PLZUCEVEg3M0zYlqqQph_oWH438ZeypqRk)
- [Example Code Repository (github)](https://github.com/wednus/hana)
- [Wednus User Forum](https://groups.google.com/d/forum/goflat)
- [PIPC Community (Naver | Korean)](http://cafe.naver.com/pipc)


Tutorials
---------
- HackIoT 01: Getting SDK for Hana
[![HackIoT 02: Hello World](https://img.youtube.com/vi/gMTeAAD0RU8/0.jpg)](https://www.youtube.com/watch?v=gMTeAAD0RU8)
- HackIoT 02: Hello World
[![HackIoT 02: Hello World](https://img.youtube.com/vi/hEUzvTp2jGs/0.jpg)](https://www.youtube.com/watch?v=hEUzvTp2jGs)
- HackIoT 03: Plug-n-Play Modules
[![HackIoT 03: Plug-n-Play Modules](https://img.youtube.com/vi/1iYv-1NqkoQ/0.jpg)](https://www.youtube.com/watch?v=1iYv-1NqkoQ)


Specifications
--------------
Onboard Features:
- Industrial-class Input range
  - DC 9~24V (30V tolerant)
- High efficiency power circuit
  - DC 5V (1.5A Peak), 3.3V
- RS485 w/ surge and ESD protection (TVS diode array)
- Protection resistor (1k ohm) between all GPIO-to-GPIO connections
- XBee Connection port
- ENC28J60 Ethernet module port
- Micro Controller
  - AVR (ATmega328P)
  - Arduino Bootloader (stock)
  - ADC: 6-channel
  - ICSP for direct Atmel Studio programming
- Power
  - 3.3V is Isolated from RPi's 3.3V rail
  - 4-pin Screw terminal block: can be attached to its side or tail.

[OPTION] Features (PCB populated):
- EEPROM: CAT34C32 pHAT ID
- RTC: DS3231 Temperature compensated high precision realtime clock

[OPTION] Accessory Adapters:
- ESP programming and others.


Pinout
------
[![Pinout Diagram](http://flat.wednus.com/_/rsrc/1549090245745/built-for-flat/hana/HackIoT%20Hana%20-%20Pinout%20Diagram.png)](http://flat.wednus.com/built-for-flat/hana)
