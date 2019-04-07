#!/bin/sh

# set prog mode
gpio mode 2 out # GPIO27(mode): 'out' && 0 => PROG | 'in' => RUN
gpio mode 7 out # GPIO4(reset): ESP reset pin
gpio write 2 0  # set PROG mode
gpio write 7 1  # reset pull-up
# trigger RUN->PROG
gpio write 7 0
gpio write 7 1
