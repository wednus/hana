#!/bin/sh

PROG_PIN=2
RESET_PIN=25

# set prog mode
gpio mode $PROG_PIN out # GPIO27(mode): 'out' && 0 => PROG | 'in' => RUN
gpio mode $RESET_PIN out # GPIO4(reset): ESP reset pin
gpio write $PROG_PIN 0  # set PROG mode
gpio write $RESET_PIN 1  # reset pull-up
# trigger RUN->PROG
gpio write $RESET_PIN 0
gpio write $RESET_PIN 1
