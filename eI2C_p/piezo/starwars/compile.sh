#!/bin/sh
gcc beep.c -o beep -lwiringPi -std=c99
gcc starwars.c -o starwars -lwiringPi -std=c99