#!/bin/sh
echo
echo "[flat] Pull the latest version.."
docker pull wednus/hackiot-hana:sdk

echo
echo "[flat] Updating Hana SDK.."
nohup docker-compose up -d &