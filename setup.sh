#!/bin/bash

arduino-cli core update-index
arduino-cli core install --additional-urls http://arduino.esp8266.com/stable/package_esp8266com_index.json esp8266:ESP8266
