#!/bin/bash

board="esp8266:esp8266:nodemcuv2"
port="/dev/ttyUSB0"
baudrate="9600"

arduino-cli monitor -b $board -p $port -c $baudrate
