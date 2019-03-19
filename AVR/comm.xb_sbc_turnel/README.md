XBee-SBC Transparent
=
***Maturity: Released***

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

## Establish Transparent (AT) Network
#### 1-on-1
Router-router; NO NEED one to be coordinator

1. Set DH and DL with partner's address (SH and SL accordingly)
2. (Optional) Set name at NI

#### 1-on-many
- Coordinator
  1. ID: unique ID for network
  2. Set CE=1 (Enable)
  3. DH=0; **DL=FFFF** (to talk to any node)
  4. AP=0 (Transparent)
- Routers
  1. ID: same as its Coordinator's
  2. JV=1 (Verifies if a coordinator exists on the same channel (CH) to join or leave if it cannot be found.)
  3. AP
      - 0 (Transparent)
      - 1 (API Mode): It is allowed for special case when router wants to know the origin of the packet.; The packet will start with '7E' and include the MAC ID.

Note: For Coordinator-Routers network in API mode, check the below:

[XCTU - Configure the XBee modules](https://www.digi.com/resources/documentation/Digidocs/90001942-13/Default.htm#tasks/t_configure_xbees_transmit_receive_data.htm%3FTocPath%3DXBee%2520API%2520mode%7CXBee%2520frame%2520exchange%7CExample%253A%25C2%25A0transmit%2520and%2520receive%2520data%7C_____1)

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