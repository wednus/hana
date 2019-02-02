Examples for HackIoT Hana SDK
=============================
This repository contains the latest example code and sub-projects for HackIoT Hana's SDK.

[![Hello World](https://img.youtube.com/vi/hEUzvTp2jGs/0.jpg)](https://www.youtube.com/watch?v=hEUzvTp2jGs)

Resources
---------
- [HackIoT Hana](http://flat.wednus.com/built-for-flat) | [flat, docker for SBCs](http://flat.wednus.com) 
- [Youtube Tutorials](https://www.youtube.com/playlist?list=PLZUCEVEg3M0zYlqqQph_oWH438ZeypqRk)
- [Example Code Repository (github)](https://github.com/wednus/hana)
- [Wednus User Forum](https://groups.google.com/d/forum/goflat)

[![Pinout Diagram](http://flat.wednus.com/_/rsrc/1549090245745/built-for-flat/hana/HackIoT%20Hana%20-%20Pinout%20Diagram.png)](http://flat.wednus.com/built-for-flat/hana)

Specifications
--------------
- Onboard Features
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

- [OPTION] Features (PCB populated)
  - EEPROM: CAT34C32 pHAT ID
  - RTC: DS3231 Temperature compensated high precision realtime clock

- [OPTION] Accessory Adapters
  - ESP programming and others.

Tested Modules
----------------
Most sample code are available in the examples folder
- OLED 128x64 (SSD1306)
- XBee X2S (Series2; ZigBee) (& all other XBee-compatible modules)
- ESP-1 (ESP8266)
- Piezo Buzzer (Generic)
- Electret Microphon (Generic)
- AVR-ISP-MK2 (OLIMEX)
- INA219 (GY-219): V-I Monitor
- ITG-MPU (GY-512)
- ADMP401 (MEMS Microphon)
- Arduino Pro Mini (3.3V)
- ENC28J60 Ethernet
- DHT22
- BME280 (GYBMEP) / BME680 (CJMCU-680)
- MAX7219
- NRF24L01*
- WS2811*
- SPI TFT (KMR-1.8)*
- IR Sensor (TSOP4838)*
- GPS*
- GY-MAX4486 Microphone
- ADS1015 (GY-ADS1115/ADS1015)
- MIC-1000 Microphone
- RS485