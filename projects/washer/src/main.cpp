//
// Created by Trevor Grayson on 3/29/23.
//
#include "Arduino.h"

#define SENSOR 5

int sensor() {
    int reading = digitalRead(SENSOR);
    return reading;
}

void setup() {
    Serial.begin(115200);
    Serial.println("start.");

    pinMode(SENSOR, INPUT);
}

void loop() {
    int reading = sensor();
    Serial.println(reading);
    //digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
}