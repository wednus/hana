#!/usr/bin/env python

import sys
sys.path.append('/workspace/libraries/Wednus/modbus-tk')

import time
import serial
import modbus_tk
import modbus_tk.defines as cst
from modbus_tk import modbus_rtu

slave_id = 1
PORT = '/dev/serial0'

def main():
    logger = modbus_tk.utils.create_logger("console")
    while 1:
        try:
            master = modbus_rtu.RtuMaster(
                serial.Serial(port=PORT, baudrate=9600, bytesize=8, parity='N', stopbits=1, xonxoff=0)
            )
            master.set_timeout(5.0)
            master.set_verbose(True)
            logger.info("connected")
    
            # We need this because the arduino resets after opening the port.
            time.sleep(2)
            ledState = master.execute(slave_id, cst.READ_HOLDING_REGISTERS, 0, 1)[0]
            logger.info(ledState)
            
            # toggle LED (AVR) on slave
            if ledState == 0:
                ledState = 1
            else:
                ledState = 0
    
            logger.info(master.execute(1, cst.WRITE_MULTIPLE_REGISTERS, 0, output_value=(ledState, )))

        except modbus_tk.modbus.ModbusError as exc:
            logger.error("%s- Code=%d", exc, exc.get_exception_code())

if __name__ == "__main__":
    main()
