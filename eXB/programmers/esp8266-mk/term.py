#!/usr/bin/env python
#
# Simple Terminal for HackIoT Hana
# - SBC <-> EXP_COMM via AVR (pass-through) Serial communication
# - 1/21/2019
# - http://flat.wednus.com/forum
# Sundew Shin - sundew@wednus.com

import os
import sys
import time
import serial
import argparse
import threading

VERSION = '1.5'
parser = argparse.ArgumentParser(description='Simple Terminal for HackIoT Hana v'+ VERSION)
parser.add_argument('-v', '--version', help='version info', action='version', version='%(prog)s v'+ VERSION)
parser.add_argument('-p', '--port', help='serial device port (default:/dev/serial0)', default='/dev/serial0')
parser.add_argument('-b', '--baud', help='baudrate (default:9600)', default='9600')
parser.add_argument('-f', '--file', help='file to upload', default='')
parser.add_argument('-m', '--mode', help='display mode string|hex (default:string)', default='string')
args = vars(parser.parse_args())

ser = serial.Serial(args['port'], args['baud'], timeout=0)   # timeout to make readline() non-blocking
ser.close()
ser.open()
ser.flushInput()
ser.isOpen()
ser.write('\r\n')
ser.flush()

os.system('clear')
_HALT = False
# Serial read in background       
def serial_monitor():
    global _HALT
    while not _HALT:
        out = ser.readline()
        if out != '':
            if args['mode'] == 'hex':
                sys.stdout.write(" ".join("{:02x}".format(ord(c)) for c in out))
                sys.stdout.write("\n")
            else:
                sys.stdout.write(out)
            sys.stdout.flush()


def main():
    global _HALT
    print "[Simple Serial Terminal] - "+ args['baud'] + "\r\nEnter 'Ctrl-C' to exit."

    # start terminal mode
    thread = threading.Thread(target=serial_monitor)
    thread.start()

    # check file upload request
    if args['file'] != '':
        upload(args.file)
        list()
        ser.close()
        sys.exit()

    try:
        while 1 :
            # get user input (will be safely queued even it's scrolled up by new data)
            input = raw_input()
            if input[:8] == ':upload ':
                upload(input[8:len(input)])
            else:
                print "\033[A                             \033[A"    # ansi escape arrow up then overwrite the line            
                ser.write(input + '\r\n')
                ser.flush()
    except KeyboardInterrupt:
        print('\r\n'+ "Good bye.")
        _HALT = True
        thread.join()
        ser.close()

if __name__ == '__main__':
    main()
