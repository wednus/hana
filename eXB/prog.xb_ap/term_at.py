#!/usr/bin/env python
#
# Simple Terminal for HackIoT Hana - AT Command Shell version
# - SBC <-> EXP_COMM via AVR (pass-through) Serial communication
# - Sundew Shin - sundew@wednus.com
# - 2/21/2019
# - http://flat.wednus.com/forum

import os
import sys
import time
import serial
import threading

PORT = '/dev/serial0'
BAUD = 9600
ser = serial.Serial(PORT, BAUD, timeout=0)   # timeout to make readline() non-blocking
ser.close()
ser.open()

os.system('clear')
_HALT = False
# serial read in background
def serial_monitor():
    global _HALT
    while not _HALT:
        out = ser.readline()
        if out != '':
            sys.stdout.write(out +'\r\n\r\n')
            sys.stdout.flush()

# start serial listener
thread = threading.Thread(target=serial_monitor)
thread.start()


def main():
    global _HALT
    # get into the AT command mode
    print("(Entering AT Command mode..)")
    time.sleep(3)
    ser.write("+++")
    print "\033[A                             \033[A"    # ansi escape arrow up then overwrite the line

    try:
        while 1 :
            # get user input (will be safely queued even it's scrolled up by new incoming data)
            input = raw_input()
            if input != '':
                ser.write(input +'\r\n')
    except KeyboardInterrupt:
        print('\r\n'+ "Good bye.")
        _HALT = True
        thread.join()
        ser.close()

if __name__ == '__main__':
    main()