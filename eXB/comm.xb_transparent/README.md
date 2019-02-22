Introduction
=
This project demonstrates how to establish XBee network and send/receive data in transparent mode.

How-to
=
1. Establish the Xbee network following the instruction below
2. Upload the main.ino sketch
3. Open term.py
4. Listen or send data to other XBee module

XBee Network Setting
=
## Tested Firmware
- XB24C
- XB9X-DM (XBee SX)
- Version 9007
- ZIGBEE TH Reg 405F

## Establish network
#### Common for 1-on-1 and 1-on-many
- ID: unique ID for network
- SC: scan channel set (set apart from nearby network's)

#### 1-on-1 transparent (passthrought)
Router-router (NO NEED one to be coordinator)
1. Set DH and DL with partner's address (SH and SL accordingly)
2. Set name at NI
3. Transparent-to-Transparent (because we cannot use XBee protocol e.g. all packets start with 7F)

#### 1-on-many transparent
- Coordinator
  1. Set CE=1 (Enable)
  2. DH=0; DL=FFFF (Talking to anyone)
  3. Transparent-to-Transparent (because we cannot use XBee protocol e.g. all packets start with 7F)
- Router
  1. JV=1 (Channel verification enable)

RS485
=
- defaults: BD=9600; NB=0; SB=0; RO=3; D6=0;  AP=0 (Transparent)
- change: D7=7(RS-485 Enable High); AO=1 (Explicit)

Hardware
=
- D0=1 (Commissioning Button)
- D5=1 (Associated indicator)

LED Indication
=
- Solid on: disconnected from the coordinator, or, coordinator is not available
- Blinking 2/sec: good communication as router
- Blinking 1/sec: work as coordinator

Commissioning Button
=
- 4-click: Reset parameters & join new network