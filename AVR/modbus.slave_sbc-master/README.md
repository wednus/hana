Modbus RTU Slave for SBC as Master
=
Implement Modbus slave on AVR

## Purpose
This program demonstrate how to implemnt Modbus RTU slave on AVR and access the registers from SBC as master.

## Requirement
- python3
- pyserial
  
## Troubleshoot

#### AttributeError: 'Serial' object has no attribute 'is_open'
You are using older version of pySerial. You can either get later version of pySerial, or use isOpen() to replace is_open.

    apt-get update && apt-get install python3 python3-pip
    pip3 install pyserial