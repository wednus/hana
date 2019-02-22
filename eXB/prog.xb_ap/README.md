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

Troubleshooting
=
### 'module' object has no attribute 'Serial'
    pip uninstall serial
    pip install pyserial