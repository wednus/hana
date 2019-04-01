#!/bin/sh
# This script uploads the specified firmware (*.bin) as an argument.

avrdude -p m328p -P /dev/serial0 -c arduino -b 57600 -U flash:w:$1