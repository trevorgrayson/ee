//
// Created by trevor on 7/30/25.
//
#include <Arduino.h>

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    if (Serial.available()) {
        String line = Serial.readStringUntil('\n');
        Serial.print("RCVD: ");
        Serial.println(line);
    }

}