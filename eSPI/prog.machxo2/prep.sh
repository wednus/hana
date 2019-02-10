#!/bin/bash
# ref: https://github.com/synthetos/PiOCD/wiki/Using-a-Raspberry-Pi-as-a-JTAG-Dongle

# install required packages
apt-get update && apt-get -y install \
  autoconf libtool libftdi-dev pkg-config libusb-1.0-0-dev

# pull external resources
mkdir build-hackiot
pwd; pushd ./build-hackiot
git clone --recursive git://git.code.sf.net/p/openocd/code openocd-git
cd openocd-git

./bootstrap
./configure --enable-sysfsgpio\
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

make && make install
cp -r tcl/* /usr/share/openocd

# test
cd /usr/share/openocd/board
wget https://gist.github.com/giseburt/e832ed40e3c77fcf7533/raw/e8c71233970e4d42eed7c3bf4b13390cdcf2a1fd/raspberrypi-due.tcl
openocd -s /usr/share/openocd -f board/raspberrypi-due.tcl

popd
