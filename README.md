Examples for HackIoT Hana SDK
=============================
This repository contains the latest examples for HackIoT Hana.
- [Buy HackIoT Hana at Tindie Store](https://www.tindie.com/products/sundew/hackiot-hana/)


Background
----------
Hana works as an IoT node in stand-alone mode forwarding data to remote partner device, and by connecting to Raspberry Pi like SBCs, it becomes IoT gateway device aggregating data from nodes and processing them for various applications.


Prerequisite
------
Assuming you are on Raspbian:

1. Update the cmdline.txt and remove 'console=serial0,115200'

        sudo nano /boot/cmdline.txt

2. Update the config.txt.

        sudo nano /boot/config.txt

    Copy-paste below at the very bottom (for overriding existing):

        dtparam=spi=on
        dtoverlay=enc28j60
        dtparam=i2c_vc=on
        dtparam=i2c_arm=on
        enable_uart=1
        dtoverlay=pi3-miniuart-bt

3. add the 'i2c-dev' to /etc/modules

        sudo bash -c "echo 'i2c-dev' >> /etc/modules"

4. Reboot

        sudo reboot


How-to
------
1. Install flat following the instruction at: [Getting flat](http://flat.wednus.com/getting_flat)

2. Install Hana SDK

    2.1. Open docker-compose.yaml file

        nano ~/docker-compose.yaml

    2.2. Add the 'hackiot' block below in the 'services' section

        services:
        ...

            hackiot:
                container_name: hackiot
                image: wednus/hackiot-hana:sdk
                volumes:
                  - /sys:/sys
                  - /etc/localtime:/etc/localtime:ro
                  - /home/pi/hackiot:/workspace
                devices:
                  - /dev/mem
                  - /dev/i2c-1
                  - /dev/gpiomem
                  - /dev/serial0
                  - /dev/spidev0.1
                ports:
                  - 80:80
                cap_add:
                  - sys_rawio
                  - sys_ptrace
                restart: always

        ...

    2.3. Create hackiot container

    <pre>
    docker-compose up -d
    </pre>

    2.4. Open SDK from web browser

    <pre>
    http://[IP Address]/
    </pre>

    Video Tutorial: [Getting SDK](https://youtu.be/gMTeAAD0RU8?t=66)

3. Check the rest of tutorials and subscibe for future updates: [HackIoT Channel](https://www.youtube.com/watch?v=gMTeAAD0RU8&list=PLZUCEVEg3M0zYlqqQph_oWH438ZeypqRk)


Getting Help
------------
- [flat User Group](https://groups.google.com/d/forum/goflat)
- [PIPC SBC Community (Naver | Korean)](http://cafe.naver.com/pipc)


Links
---------
- [HackIoT Hana Page](http://flat.wednus.com/built-for-flat)
- [Example Code Github](https://github.com/wednus/hana)


Pinout
------
[![Pinout Diagram](http://flat.wednus.com/_/rsrc/1549090245745/built-for-flat/hana/HackIoT%20Hana%20-%20Pinout%20Diagram.png)](http://flat.wednus.com/built-for-flat/hana)
