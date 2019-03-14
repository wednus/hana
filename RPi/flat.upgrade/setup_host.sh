#!/bin/sh
test_seq="Image is up to date"
echo
echo "[flat] Pull the latest version.."
MSG=$(docker pull flab/flat:latest)


if [[ $MSG =~ $test_seq ]];
then
  echo
  echo "Already up to date."
  exit
else
    echo
    echo "[flat] Updating flat.."
    nohup docker-compose up -d &
fi