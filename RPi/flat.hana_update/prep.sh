#!/bin/sh
clear
echo "[flat] Login to host"
ssh pi@host 'bash -s' < setup_host.sh
