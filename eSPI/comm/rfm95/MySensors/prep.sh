#!/bin/sh

MYSENS="/workspace/libraries/Wednus/MySensors"

oldpath=`pwd`
cd $MYSENS

./configure \
  --soc=BCM2835 \
  --my-gateway=ethernet --my-port=502 \
  --spi-spidev-device=/dev/spidev0.1 \
  --my-transport=rfm95 \
  --my-rfm95-frequency=868 \
  --my-rfm95-irq-pin=25 \
  --my-rfm95-cs-pin=8

make

cd $oldpath

cp $MYSENS/bin/mysgw ./