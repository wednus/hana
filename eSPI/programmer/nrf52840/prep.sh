#!/bin/sh

# install required packages
apt-get update && apt-get -y install \
  autoconf libtool libftdi-dev pkg-config libusb-1.0-0-dev telnet

OCD="/workspace/libraries/Wednus/openocd-git"
oldpath=`pwd`
cd $OCD

#make install
/bin/mkdir -p '/usr/bin'
/bin/bash ./libtool   --mode=install /usr/bin/install -c src/openocd '/usr/bin'
/usr/bin/install -c src/openocd /usr/bin/openocd
/bin/mkdir -p '/usr/share/openocd/OpenULINK'
/usr/bin/install -c -m 644 src/jtag/drivers/OpenULINK/ulink_firmware.hex '/usr/share/openocd/OpenULINK'

/bin/mkdir -p '/usr/share/info'
/bin/mkdir -p '/usr/share/man/man1'
/usr/bin/install -c -m 644 doc/openocd.1 '/usr/share/man/man1'
/bin/mkdir -p '/usr/share/openocd'
/bin/mkdir -p '/usr/share/openocd/contrib'
/usr/bin/install -c -m 644  contrib/60-openocd.rules '/usr/share/openocd/contrib'
/bin/mkdir -p '/usr/share/openocd/contrib/libdcc'
/usr/bin/install -c -m 644  contrib/libdcc/dcc_stdio.c contrib/libdcc/dcc_stdio.h contrib/libdcc/example.c contrib/libdcc/README '/usr/share/openocd/contrib/libdcc'
 
cp -r tcl/ /usr/share/openocd

cd $oldpath

# test
openocd
