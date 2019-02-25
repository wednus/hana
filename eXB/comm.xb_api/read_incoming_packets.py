#! /usr/bin/env python

from xbee.thread import XBee, ZigBee
import serial

ser = serial.Serial('/dev/serial0', 9600)
xbee = ZigBee(ser)

while True:
    try:
        response = xbee.wait_read_frame()
        print response
    except KeyboardInterrupt:
        break

ser.close()
