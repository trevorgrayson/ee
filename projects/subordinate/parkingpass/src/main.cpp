//
// Created by trevor on 5/27/24.
//
#include <Arduino.h>
#include "wifistrength.h"


void setup()
{
    Serial.begin(9600);
    setupWifi();
}

void loop()
{
    Serial.println(strength());
}
