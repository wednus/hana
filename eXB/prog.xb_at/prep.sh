#!/bin/sh

apt-get update
apt-get -y install python3-pip && sudo apt-get install python3-serial && sudo pip3 install digi-xbee
#git clone https://github.com/digidotcom/python-xbee.git