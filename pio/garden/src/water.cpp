//
// Created by trevor on 1/28/23.
//
#include<Arduino.h>

#define ONE_MEASURE 10 * 1000 // seconds


void waterConditionally(int motor, int sensor) {
    Serial.print("MOISTURE LEVEL:");
    float value = analogRead(sensor);
    Serial.println(value);
    if(value>750)
    {
        digitalWrite(motor, LOW);
    }
    else
    {
        digitalWrite(motor, HIGH);
    }
}

void water(int pin) {
    digitalWrite(pin, LOW);
    delay(ONE_MEASURE);
    digitalWrite(pin, HIGH);
}