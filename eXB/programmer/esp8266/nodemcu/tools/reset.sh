#!/bin/sh

RESET_PIN=25    # GPIO26(reset): ESP reset pin

# reset
gpio mode $RESET_PIN out
gpio write $RESET_PIN 1  # reset pull-up
gpio write $RESET_PIN 0  # reset
sleep 1
gpio write $RESET_PIN 1