#!/bin/sh

# software trigger rejoin

gpio mode 4 out # GPIO23(mode)
gpio write 4 0  # reset
sleep 1
gpio write 4 1  # reset
#gpio mode 4 in  # GPIO23(mode)

exit 0