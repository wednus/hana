#!/bin/sh
# ref: https://github.com/synthetos/PiOCD/wiki/Using-a-Raspberry-Pi-as-a-JTAG-Dongle

# install required packages
#apt-get update && apt-get -y install \
#  autoconf libtool libftdi-dev pkg-config libusb-1.0-0-dev

OCD="/workspace/libraries/Wednus/openocd-git"
oldpath=`pwd`
cd $OCD

./bootstrap
./configure --enable-sysfsgpio\
    --enable-bcm2835gpio \
    --enable-maintainer-mode \
    --disable-werror \
    --enable-ft2232_libftdi \
    --enable-ep93xx \
    --enable-at91rm9200 \
    --enable-usbprog \
    --enable-presto_libftdi \
    --enable-jlink \
    --enable-vsllink \
    --enable-rlink \
    --enable-arm-jtag-ew \
    --enable-dummy \
    --enable-buspirate \
    --enable-ulink \
    --enable-presto_libftdi \
    --enable-usb_blaster_libftdi \
    --enable-ft2232_libftdi\
    --prefix=/usr

make
make install
cp -r tcl/ /usr/share/openocd

cd $oldpath

# test
openocd
