#!/bin/sh
clear
echo "[flat] Login to host"
ssh -o StrictHostKeyChecking=no pi@host 'bash -s' < setup_host.sh
