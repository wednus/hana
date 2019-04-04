#!/usr/bin/python
# This program resets the AVR in HackIoT Hana board.

import time
import RPi.GPIO as GPIO

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)

pin = 17
GPIO.setup(pin, GPIO.OUT)
GPIO.output(pin, GPIO.HIGH)
time.sleep(0.12)
GPIO.output(pin, GPIO.LOW)
