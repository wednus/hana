#!/usr/bin/env python
# -*- coding: utf_8 -*-
"""
 Modbus TestKit: Implementation of Modbus protocol in python

 (C)2009 - Luc Jean - luc.jean@gmail.com
 (C)2009 - Apidev - http://www.apidev.fr

 This is distributed under GNU LGPL license, see license.txt
"""

import sys
sys.path.append('/workspace/libraries/python/modbus-tk')

import modbus_tk
import modbus_tk.defines as cst
from modbus_tk import modbus_rtu
import serial

PORT = '/dev/serial0'

def main():
    """main"""
    logger = modbus_tk.utils.create_logger(name="console", record_format="%(message)s")

    #Create the server
    server = modbus_rtu.RtuServer(serial.Serial(PORT))

    try:
        logger.info("running...")
        logger.info("enter 'quit' for closing the server")

        server.start()
        
        # Sundew: self-registered as Slave ID# = 1
        slave_1 = server.add_slave(1)
        # Sundew: creating a block starting at address:0 w/ length=100
        # Add a new block identified by its name
        # add_block(self, block_name, block_type, starting_address, size):
        # new block shouldn't overlap an existing
        # it means that only 1 block per type must correspond to a given address
        # for example: it must not have 2 holding registers at address 100
        #supported block types
        #COILS = 1
        #DISCRETE_INPUTS = 2
        #HOLDING_REGISTERS = 3
        #ANALOG_INPUTS = 4
        slave_1.add_block('0', cst.HOLDING_REGISTERS, 0, 100)

        while True:
            cmd = sys.stdin.readline()
            args = cmd.split(' ')

            if cmd.find('quit') == 0:
                sys.stdout.write('bye-bye\r\n')
                break

            elif args[0] == 'add_slave':
                slave_id = int(args[1])
                server.add_slave(slave_id)
                sys.stdout.write('done: slave %d added\r\n' % (slave_id))
            # Sundew added
            elif args[0] == 'get_slave':
                slave_id = int(args[1])
                slave = server.get_slave(slave_id)
                sys.stdout.write('done: got slave\r\n' % (str(slave)))

            elif args[0] == 'add_block':
                slave_id = int(args[1])
                name = args[2]
                block_type = int(args[3])
                starting_address = int(args[4])
                length = int(args[5])
                slave = server.get_slave(slave_id)
                slave.add_block(name, block_type, starting_address, length)
                sys.stdout.write('done: block %s added\r\n' % (name))

            # Sundew added
            elif args[0] == '_get_block':
                slave_id = int(args[1])
                name = args[2]
                slave = server.get_slave(slave_id)
                block = slave._get_block(name)
                sys.stdout.write('done: got block\r\n' % (str(block)))
            # Sundew added
            elif args[0] == 'remove_block':
                slave_id = int(args[1])
                name = args[2]
                slave = server.get_slave(slave_id)
                slave.remove_block(name)
                sys.stdout.write('done: block %s removed\r\n' % (name))
            # Sundew added
            elif args[0] == 'remove_all_blocks':
                slave_id = int(args[1])
                slave = server.get_slave(slave_id)
                slave.remove_all_blocks()
                sys.stdout.write('done: all blocks are removed\r\n')

            elif args[0] == 'set_values':
                slave_id = int(args[1])
                name = args[2]
                address = int(args[3])
                values = []
                for val in args[4:]:
                    values.append(int(val))
                slave = server.get_slave(slave_id)
                slave.set_values(name, address, values)
                values = slave.get_values(name, address, len(values))
                sys.stdout.write('done: values written: %s\r\n' % (str(values)))
            elif args[0] == 'get_values':
                slave_id = int(args[1])
                name = args[2]
                address = int(args[3])
                length = int(args[4])
                slave = server.get_slave(slave_id)
                values = slave.get_values(name, address, length)
                sys.stdout.write('done: values read: %s\r\n' % (str(values)))

            else:
                sys.stdout.write("unknown command %s\r\n" % (args[0]))
    finally:
        server.stop()

if __name__ == "__main__":
    main()
