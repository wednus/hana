#!/bin/sh
PORT="80"
BACKUP="docker-compose_backup_$(date +'%m%d%y_%H%M%S').yaml"

echo
echo "[flat] Backup docker-compose.yaml .."
mv ./docker-compose.yaml ./${BACKUP}

echo
echo "[flat] Update docker-compose.yaml.."
sed '/services:/a \
  rpi-monitor:\
    container_name: rpi-monitor\
    image: wednus/rpi-monitor\
    ports:\
      - '${PORT}':8888\
    ' ~/${BACKUP} > ~/docker-compose.yaml

echo
echo "[flat] Create container.."
docker-compose up -d --remove-orphans

echo
echo "[flat] Completed."
echo "Open 'http://[IP Address]:${PORT}' in web browser."