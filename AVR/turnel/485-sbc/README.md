RS485-SBC Transparent
=
***Maturity: Production***

This program creates turnel between RS485 and SBC, so data come in one end forwarded to the other end transparently.

### Example
- A sample data request frame with STX=02 and ETX=03

      02 01 00 01 01 03 06 00 00 00 00 05 A6 03

- A sample response with data and trailing check bits

      02 01 01 01 01 03 06 0A 8C 03 20 03 13 FF 64 00 00 30 F0 03 00 0F 36 46 03