Introduction
=
This project demonstrates how to modify parameter settings of XBee in transparent (AT) mode.

How-to
=
1. Establish the Xbee network
2. Upload the main.ino sketch
3. Use AT Commander (ATComm.py) for configuring XBee in transparent mode

Tools
=
### term_at.py
Interactive AT command shell

    usage: term_at.py
Once the device is in Command mode, it listens for user input for a while.
If 10 seconds go by without any user input, the device automatically drops out of Command mode and returns to Transparent mode.
When that happen, you can simply restart the program.

### ATComm.py
Batch execute AT commands

    usage: ATComm.py [-h] [-v] [-c COMMANDS [COMMANDS ...]] [-p PORT] [-b BAUD]

    AT Commander v1.0

    optional arguments:
      -h, --help            show this help message and exit
      -v, --version         version info
      -c COMMANDS [COMMANDS ...], --commands COMMANDS [COMMANDS ...]
                            AP Commands (parameter:value)
      -p PORT, --port PORT  serial device port (default:/dev/serial0)
      -b BAUD, --baud BAUD  baudrate (default:9600)

##### Read
ATComm.py -c NI: DH: DL:

    ATNI
    test

    ATDH
    13A200

    ATDL
    40F7478B

##### Write
ATComm.py -c NI:hana DH:13A200 DL:40FFFFF0

    ATNI hana
    OK

    ATDH 13A200
    OK

    ATDL 40FFFFF0
    OK
##### Mixed
ATComm.py -c NI: DH: DL:40F7478B

    ATNI
    hana

    ATDH
    13A200

    ATDL 40F7478B
    OK

Note: You can also use XCTU for sending AT command to local XBee module.

##### Examples
- Join coordinator on PAN ID=45 as a transparent node

      ./ATComm.py -c ID:45 JV:1 AP:0

[XCTU - Generate the AT command frame](https://www.digi.com/resources/documentation/Digidocs/90001942-13/Default.htm#tasks/t_generate_at_command_frame.htm%3FTocPath%3DXBee%2520API%2520mode%7CXBee%2520frame%2520exchange%7CExample%253A%2520configure%2520your%2520local%2520XBee%2520module%7C_____3)

Troubleshoot
=
### 'module' object has no attribute 'Serial'
- cause: wrong 'serial' python module installed

Uninstall and reinstall the correct module:

    pip uninstall serial
    pip install pyserial

### No 'OK' prompt
- cause: XBee module is in API mode or using API firmware (e.g. 'ZigBee Router API')

Connect the module to a PC; use XCTU and switch to an AT firmware ('ZigBee Router AT')