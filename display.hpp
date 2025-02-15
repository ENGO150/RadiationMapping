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

namespace display
{
    void begin(void); //INIT LCD DISPLAY
    void print(String line_1, String line_2); //PRINT INTO LCD (OVERWRITING)
    void print(String line_1, String line_2, bool end); //PRINT INTO LCD WITH OPTION TO PRINT FROM END
}
