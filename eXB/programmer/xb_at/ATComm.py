#!/usr/bin/env python
#
# ATComm, AT Commander in python
# - Batch execute AT commands
# - Sundew Shin - sundew@wednus.com
# - 2/21/2019
# - http://flat.wednus.com/forum
VERSION = '1.0'

import os
import sys
import time
import serial
import argparse
import threading

def pair(arg):
    return [x for x in arg.split(':')]

parser = argparse.ArgumentParser(description='AT Commander v'+ VERSION)
parser.add_argument('-v', '--version', help='version info', action='version', version='%(prog)s v'+ VERSION)
parser.add_argument('-p', '--port', help='serial device port (default:/dev/serial0)', default='/dev/serial0')
parser.add_argument('-b', '--baud', help='baudrate (default:9600)', default='9600')
parser.add_argument('commands', help='AP Commands (parameter:value)', type=pair, nargs='+')
args = vars(parser.parse_args())

ser = serial.Serial(args['port'], args['baud'], timeout=0)   # timeout to make readline() non-blocking
ser.close()
ser.open()

# exit for no -c arguments
if not args['commands']:
    print('Nothing to do. For help, use \'ATComm.py -h\''+ '\r\n')
    exit()

# add ATWR to save change(s) made
args['commands'].append(['WR',''])
args['commands'].append(['CN',''])
# first-in first-out
args['commands'].reverse()

_HALT = False
# serial read in background
def serial_monitor():
    global _HALT
    while not _HALT:
        out = ser.readline()
        #if out == 'OK\r':
        if out != '':
            sys.stdout.write(out +'\r\n\r\n')
            sys.stdout.flush()
            if args['commands']:
                exec_command()
            else:
                _HALT = True
                ser.close()
                os._exit(0)

# start serial listener
thread = threading.Thread(target=serial_monitor)
thread.start()


def exec_command():
    cmd = args['commands'].pop()
    cmd_str = 'AT'+ cmd[0]
    if cmd[1] != '':
        cmd_str += ' '+ cmd[1]
    ser.write(cmd_str +'\r\n')
    print(cmd_str)


def main():
    global _HALT
    # get into the AT command mode
    print("(Entering AT Command mode..)")
    time.sleep(5)   # preceeding guard time silence
    ser.write("+++")
    time.sleep(1)   # following guard time silence

    try:
        while 1:
            time.sleep(0.1)
    except KeyboardInterrupt:
        _HALT = True
        thread.join()
        ser.close()

if __name__ == '__main__':
    main()