#!/bin/sh
clear
echo "[flat] Login to host.."
ssh pi@host 'bash -s' < setup_host.sh

IP=$(curl -s -L http://ifconfig.me)
IP_TOR=$(curl -s --socks http://host:9050 -L http://ifconfig.me)

echo "\n[flat] Testing.."

echo "IP (original): ${IP}"
echo "IP (torred): ${IP_TOR}"
