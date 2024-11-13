#!/bin/bash

board="esp8266:esp8266:nodemcuv2"
port="/dev/ttyUSB0"

arduino-cli compile -b $board -p $port $(pwd | rev | cut -d "/" -f 1 | rev).ino
arduino-cli upload -b $board -p $port $(pwd | rev | cut -d "/" -f 1 | rev).ino
