#!/bin/bash

# This is part of RadiationMapping
# Copyright (C) 2024 Václav Šmejkal

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

board="esp32:esp32:esp32c3"
port="/dev/ttyACM0"
baudrate="9600"

arduino-cli monitor -b $board -p $port -c $baudrate --timestamp
