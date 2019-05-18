nRF52840 Programming
=

## Hana.eSPI.BT840 Module

- nRF52840 Development Kit (DK:pca10056) Compatible
  - LED 0/1/2/3 (P0.13/14/15/16)
  - BTN 1/2/3/4 (P0.11/12/24/25)


## Preparation
#### JTAG (SWD) and OpenOCD
    ../jtag/prep.sh

#### Getting toolchain
    sed -i 's/jessie/stretch/g' /etc/apt/sources.list && grep -lnr jessie /etc/apt
    apt-get update && apt-get upgrade -y && apt-get dist-upgrade -y && apt-get autoremove -y && apt-get autoclean && apt-get install -y gcc-arm-none-eabi


## Troubleshoot
#### Programming
- Cannot erase protected sector at 0x

      nrf5 mass_erase
      program /workspace/hana_1.5/eSPI/programmer/___bt840/BT840_AT_115200_181113/BT840_AT_3in1PC181113.hex
