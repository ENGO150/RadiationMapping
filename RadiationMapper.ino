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

#include <list>

#define INPUT_PIN D6 //VIN PIN FOR GEIGER COUNTER
#define MEASUREMENT_TIME_MS 60000 //MINUTE

std::list<unsigned long> counts; //COUNTS IN LAST MINUTE (OR MEASUREMENT_TIME_MS IF MODIFIED)

//CALLBACK WHEN RADIATION PARTICLE IS DETECTED
void IRAM_ATTR increment_counts()
{
    counts.push_back(millis()); //APPEND CURRENT TIME TO LIST counts
}

void setup()
{
    //SERIAL COMMUNICATION INIT
    Serial.begin(9600);

    //INIT PINS
    pinMode(INPUT_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(INPUT_PIN), increment_counts, FALLING);
}

int last_counts = -1;
void loop()
{
    unsigned long current_millis = millis(); //CURRENT TIME
    int current_counts = 0;

    //REMOVE COUNTS OLDER THAN MEASUREMENT_TIME_MS
    counts.remove_if([current_millis](unsigned long particle) //haha, *lambda* (cries in pure-C)
    {
        return (current_millis - particle >= MEASUREMENT_TIME_MS);
    });

    //COUNT RECENT
    current_counts = counts.size();

    if (last_counts != current_counts) //PRINT CPM IF CHANGED
    {
        last_counts = current_counts;
        Serial.println(String(current_counts) + " CPM");
    }
}
