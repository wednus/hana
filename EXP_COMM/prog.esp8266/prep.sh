#!/bin/bash

pip install esptool

# pull external resources
mkdir build-hackiot
pwd; pushd ./build-hackiot
git clone https://github.com/espressif/ESP8266_NONOS_SDK
cd ESP8266_NONOS_SDK/bin

popd