Modbus RTU Slave
=
Implement Modbus slave on AVR and SBC as master

## Purpose
This program demonstrate how to implemnt Modbus RTU slave on AVR and access the registers from SBC as master.

## Requirement
- pyserial
  
## How-to
1. Upload the main.ino
2. Run the testing program.

       python ./rtu_master.py
    

## Troubleshoot

#### AttributeError: 'Serial' object has no attribute 'is_open'
Run with the command:

    python ./rtu_master.py
    
#### modbus_tk.modbus.ModbusInvalidResponseError: Response length is invalid 0
- cause: the Modbus Slave is not running
