#!/bin/sh

# reset
gpio mode 2 in  # GPIO27(mode): 'out' && 1 => PROG | 'in' => RUN
gpio mode 7 out # GPIO4(reset): ESP reset pin
gpio write 7 1  # reset pull-up
gpio write 7 0  # reset
gpio write 7 1