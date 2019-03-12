#!/bin/sh
ssh pi@172.18.0.1 'bash -s' < setup_host.sh

IP=$(curl -L http://ifconfig.me)
IP_TOR=$(curl --socks http://172.18.0.1:9050 -L http://ifconfig.me)

echo "/n[flat] Testing.."

echo "IP (original): ${IP}"
echo "IP (torred): ${IP_TOR}"
