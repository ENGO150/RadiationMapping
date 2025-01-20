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

#include <DHT.h>
#include <DHT_U.h>

#include <ArduinoJson.h>

#include "display.hpp"

#define INPUT_PIN 10 //VIN PIN FOR GEIGER COUNTER
#define MEASUREMENT_TIME_MS 60000 //MINUTE
#define SEND_TIME_MS 1000 //HOW OFTEN TO SEND DATA
#define CALIBRATION_FACTOR 0.00332 //CONSTANT FOR CONVERTING J305 CPM TO uSv/h

std::list<unsigned long> counts; //COUNTS IN LAST MINUTE (OR MEASUREMENT_TIME_MS IF MODIFIED)
unsigned long last_send_time = 0;

//CALLBACK WHEN RADIATION PARTICLE IS DETECTED
void IRAM_ATTR increment_counts() //TODO: Possible noise
{
    counts.push_back(millis()); //APPEND CURRENT TIME TO LIST counts
}

//DHT11 STUFF
DHT_Unified dht(9, DHT11);
JsonDocument doc;
sensors_event_t event;

void setup()
{
    Serial.begin(9600);

    //INIT DHT11
    dht.begin();
    sensor_t sensor;
    dht.temperature().getSensor(&sensor);
    dht.humidity().getSensor(&sensor);

    //INIT LCD
    display::begin();

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
        display::print(String(current_counts) + " CPM", String(current_counts * CALIBRATION_FACTOR) + " uSv/h"); //TODO: Replace with OLED

        dht.temperature().getEvent(&event);
        display::print(String((int) event.temperature) + "C", "", true);

        dht.humidity().getEvent(&event);
        display::print("", String((int) event.relative_humidity) + "%", true);
    }

    //SEND CURRENT STATE IN JSON
    if (current_millis - last_send_time >= SEND_TIME_MS)
    {
        //SERIALIZE
        doc["cpm"] = counts.size();

        dht.temperature().getEvent(&event);
        doc["temperature"] = event.temperature;

        dht.humidity().getEvent(&event);
        doc["humidity"] = event.relative_humidity;

        serializeJson(doc, Serial); //SEND
        Serial.println(); //TODO: Implement WiFi

        last_send_time = current_millis;
    }
}
