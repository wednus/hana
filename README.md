Examples for HackIoT Hana SDK
=============================
This repository contains the latest examples for HackIoT Hana.

Background
----------
Hana works as an IoT node in stand-alone mode forwarding data to remote partner device, and by connecting to Raspberry Pi like SBCs, it becomes IoT gateway device aggregating data from nodes and processing them for various applications.

How-to
------
Assuming you are on Raspbian.

1. Update /boot/cmdline.txt
    Remove 'console=serial0,115200'

2. Update '/boot/config.txt' by adding the bottom the below at :

    dtparam=spi=on
    dtoverlay=enc28j60
    dtparam=i2c_vc=on
    dtparam=i2c_arm=on
    dtoverlay=i2c-rtc,ds3231
    enable_uart=1
    dtoverlay=pi3-miniuart-bt

3. Reboot
	*sudo shutdown -h now*

Links
---------
- [HackIoT Hana](http://flat.wednus.com/built-for-flat) | [flat, docker for SBCs](http://flat.wednus.com)
- [Tindie Store](https://www.tindie.com/products/sundew/hackiot-hana/)
- [Youtube Tutorials](https://www.youtube.com/playlist?list=PLZUCEVEg3M0zYlqqQph_oWH438ZeypqRk)
- [Example Code Repository (github)](https://github.com/wednus/hana)
- [Wednus User Forum](https://groups.google.com/d/forum/goflat)
- [PIPC Community (Naver | Korean)](http://cafe.naver.com/pipc)



Pinout
------
[![Pinout Diagram](http://flat.wednus.com/_/rsrc/1549090245745/built-for-flat/hana/HackIoT%20Hana%20-%20Pinout%20Diagram.png)](http://flat.wednus.com/built-for-flat/hana)
