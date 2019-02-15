Examples for HackIoT Hana SDK
=============================
This repository contains the latest examples for HackIoT Hana.

Background
----------
Hana works as an IoT node in stand-alone mode forwarding data to remote partner device, and by connecting to Raspberry Pi like SBCs, it becomes IoT gateway device aggregating data from nodes and processing them for various applications.

Prerequisite
------
Assuming you are on Raspbian:

1. Update /boot/cmdline.txt.
Remove 'console=serial0,115200'

2. Update /boot/config.txt. *sudo nano /boot/config.txt*

Copy-paste below at the very bottom (for overriding existing):
>dtparam=spi=on<br>
dtoverlay=enc28j60<br>
dtparam=i2c_vc=on<br>
dtparam=i2c_arm=on<br>
dtoverlay=i2c-rtc,ds3231<br>
enable_uart=1<br>
dtoverlay=pi3-miniuart-bt

3. Reboot *sudo shutdown -h now*




How-to
------
1. Install flat following the instruction at: [Getting flat](http://flat.wednus.com/getting_flat)

2. Install Hana SDK: [Getting SDK](https://youtu.be/gMTeAAD0RU8?t=66)

3. Check the rest of tutorials at HackIoT channel and subscibe for future updates.

[HackIoT Youtube channel](https://www.youtube.com/watch?v=gMTeAAD0RU8&list=PLZUCEVEg3M0zYlqqQph_oWH438ZeypqRk)


Links
---------
- [HackIoT Hana](http://flat.wednus.com/built-for-flat) | [flat, docker for SBCs](http://flat.wednus.com)
- [Tindie Store](https://www.tindie.com/products/sundew/hackiot-hana/)
- [Example Code Repository (github)](https://github.com/wednus/hana)
- [Wednus User Forum](https://groups.google.com/d/forum/goflat)
- [PIPC Community (Naver | Korean)](http://cafe.naver.com/pipc)



Pinout
------
[![Pinout Diagram](http://flat.wednus.com/_/rsrc/1549090245745/built-for-flat/hana/HackIoT%20Hana%20-%20Pinout%20Diagram.png)](http://flat.wednus.com/built-for-flat/hana)
