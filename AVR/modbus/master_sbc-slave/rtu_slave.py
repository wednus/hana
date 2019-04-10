#!/usr/bin/env python3

import sys
sys.path.append('/workspace/libraries/Wednus/modbus-tk')

import modbus_tk
import modbus_tk.defines as cst
from modbus_tk import modbus_rtu
import serial
PORT = '/dev/serial0'

def main():
    logger = modbus_tk.utils.create_logger(name="console", record_format="%(message)s")
    server = modbus_rtu.RtuServer(serial.Serial(PORT))

    try:
        logger.info("running...")
        logger.info("enter 'quit' for closing the server")

        server.start()
        
        # self-registering as Slave ID# = 1
        slave_1 = server.add_slave(1)
        # creating a block starting at address:0 w/ length=1
        # add_block(self, block_name, block_type, starting_address, size):
        # Add a new block identified by its name; new block shouldn't overlap an existing
        # it means that only 1 block per type must correspond to a given address
        # for example: it must not have 2 holding registers at address 0
        slave_1.add_block('0', cst.HOLDING_REGISTERS, 0, 1)

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
            elif args[0] == '_get_block':
                slave_id = int(args[1])
                name = args[2]
                slave = server.get_slave(slave_id)
                block = slave._get_block(name)
                sys.stdout.write('done: got block\r\n' % (str(block)))
            elif args[0] == 'remove_block':
                slave_id = int(args[1])
                name = args[2]
                slave = server.get_slave(slave_id)
                slave.remove_block(name)
                sys.stdout.write('done: block %s removed\r\n' % (name))
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
