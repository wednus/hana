HackIoT Hana
================
Demo Projects for SDK
-------------
This repository contains the demo projects for the SDK of HackIoT Hana.

IMPORTANT: The project code here assumes the target SBC's specific H/W (e.g. RPi+Hana) and S/W environment prepared as docker images.
All docker images introduced here are freely available as well.

About Hana
------------------
Hana works as an IoT node in stand-alone mode forwarding data to remote partner device, and paried with a Raspberry Pi like SBC, it becomes IoT gateway device aggregating data from nodes and processing them for various applications.
- [Buy HackIoT Hana at Tindie](https://www.tindie.com/products/sundew/hackiot-hana/)


Preparation
-----------
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

4. Install docker and flat running the command:

       curl http://host.wednus.com/getflat | sh

    For more information: [Getting flat](http://flat.wednus.com/getting_flat)

5. Reboot

       sudo reboot

Getting SDK
-----------
This section explains how to obtain SDK with examples within docker container environment that everything is already configured.

For a quick video tutorial, watch [Getting SDK for HackIoT Hana](https://youtu.be/gMTeAAD0RU8?t=66).

1. Install Hana SDK

    1.1. Open docker-compose.yaml file

       nano ~/docker-compose.yaml

    1.2. Add the 'hackiot' block below in the 'services' section

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
        
    Note: The image 'wednus/hackiot-hana:sdk' contains SDK & this demo projects as well. For SDK without demos, use 'wednus/hackiot-hana' instead.

    1.3. Create hackiot container

       docker-compose up -d

    1.4. Open SDK from web browser

       http://[IP Address]/

2. Check the other tutorials and subscibe for future updates:
 
   [HackIoT Youtube Channel](https://www.youtube.com/watch?v=gMTeAAD0RU8&list=PLZUCEVEg3M0zYlqqQph_oWH438ZeypqRk)

SDK Updater
-----------
1. In the SDK (cloud9) IDE, open 'RPi/flat.hana_upgrade' sub-project.
2. Open README.md file and follow the instruction.


Getting Help
------------
- [flat User Group](https://groups.google.com/d/forum/goflat)
- [PIPC SBC Community (Naver | Korean)](http://cafe.naver.com/pipc)


Links
-----
- [HackIoT Hana Page](http://flat.wednus.com/built-for-flat)
- [Example Code Github](https://github.com/wednus/hana)


Pinout
------
[![Pinout Diagram](http://flat.wednus.com/_/rsrc/1549090245745/built-for-flat/hana/HackIoT%20Hana%20-%20Pinout%20Diagram.png)](http://flat.wednus.com/built-for-flat/hana)


Troubleshoot
------------
#### During AVR upload
- [ERROR] avrdude-hackiot: stk500_getparm(): (a) protocol error, expect=0x14, resp=0x00
    - Check /boot/cmdline.txt and make sure the removal of ‘console=serial0,115200’
- [ERROR] avrdude-hackiot: stk500_getsync() attempt 1 of 10: not in sync: resp=0x00
    - cause: /dev/serial0 is not available
    - Make sure there's no program occupying serial0. (e.g. python scripts)

#### The Last Resort
If all your troubleshoot effort failed, you may want to start over from reflashing the micro SD card.
