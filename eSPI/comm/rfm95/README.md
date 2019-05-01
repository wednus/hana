Build
---------

./configure \
  --soc=BCM2835 \
  --my-gateway=ethernet --my-port=502 \
  --spi-spidev-device=/dev/spidev0.1 \
  --my-transport=rfm95 \
  --my-rfm95-frequency=868 \
  --my-rfm95-irq-pin=25 \
  --my-rfm95-cs-pin=8
  

For node operation (non-gateway), add:
./configure \
  --soc=BCM2835 \
  --spi-spidev-device=/dev/spidev0.1 \
  --my-transport=rfm95 \
  --my-rfm95-frequency=868 \
  --my-rfm95-irq-pin=25 \
  --my-rfm95-cs-pin=8 \
  --my-node-id=10
  
For mqtt gateway:
./configure \
  --soc=BCM2835 \
  --my-gateway=mqtt \
  --my-controller-ip-address=127.0.0.1 \
  --my-mqtt-publish-topic-prefix=my-out \
  --my-mqtt-subscribe-topic-prefix=my-in \
  --my-mqtt-client-id=mygt \
  --spi-spidev-device=/dev/spidev0.1 \
  --my-transport=rfm95 \
  --my-rfm95-frequency=868 \
  --my-rfm95-irq-pin=25 \
  --my-rfm95-cs-pin=8
