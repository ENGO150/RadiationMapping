/*
This is part of RadiationMapping
Copyright (C) 2024 Václav Šmejkal

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "display.hpp"

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2, 16);

namespace display
{
    void begin(void)
    {
        //INIT THE LCD ITSELF
        Wire.begin(6, 7);
        lcd.init();

        //TURN ON THE BACKLIGHT
        lcd.backlight();
    }

    void print(String line_1, String line_2)
    {
        print(line_1, line_2, false);
    }

    void print(String line_1, String line_2, bool end)
    {
        //CLEAR
        if (!end) lcd.clear();

        //LINE 1
        if (line_1 != "")
        {
            lcd.setCursor(end ? 16 - line_1.length() : 0, 0);
            lcd.print(line_1);
        }

        //LINE 2
        if (line_2 != "")
        {
            lcd.setCursor(end ? 16 - line_2.length() : 0, 1);
            lcd.print(line_2);
        }
    }
}
