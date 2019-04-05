Modbus RTU Master
=
Implement Modbus master on AVR

## Purpose
This program demonstrate how to implemnt Modbus RTU master on AVR and access the registers from SBC as slave.


## How-to
First, run:

    python3 ./rtu_slave.py

Set the register value:

    set_values 1 0 0 5

Use the following in code block for 'setup()' in Arduino code reading the register value '7'.
This function will blink the LED (AVR) 7 times.

    packet1->id = 1;
    packet1->function = READ_HOLDING_REGISTERS;
    packet1->address = 0;
    packet1->no_of_registers = 1;
    packet1->register_array = regs;
    

## Requirement
- python3
- pyserial
  
## Troubleshoot

#### AttributeError: 'Serial' object has no attribute 'is_open'
You are using older version of pySerial. You can either get later version of pySerial, or use isOpen() to replace is_open.

For pySerial v3.x, you need to install python3 first.

    apt-get update && apt-get install python3 python3-pip
    pip3 install pyserial