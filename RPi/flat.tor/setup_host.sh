#!/bin/sh
BACKUP="docker-compose_backup_$(date +'%m%d%y_%H%M%S').yaml"

echo
echo "[flat] Backup docker-compose.yaml .."
mv ./docker-compose.yaml ./${BACKUP}

echo
echo "[flat] Update docker-compose.yaml.."
sed '/services:/a \
  tor:\
    container_name: tor\
    image: wednus/rpi-torproxy\
    network_mode: "host"\
    ' ~/${BACKUP} > ~/docker-compose.yaml

echo
echo "[flat] Create container.."
docker-compose up -d --remove-orphans

echo
echo "[flat] Completed."