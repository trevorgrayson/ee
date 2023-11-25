//
// Created by trevor on 9/16/2023.
//
#include "Arduino.h"
#include "presence.h"
#include "pins.h"

void setup()
{
    Serial.begin(9600);
    setupPresence();
}

void loop()
{
    Serial.print(motionLevel());
//    Serial.print("\t");
//    Serial.print(noiseLevel());
    Serial.println();
    analogWrite(MIC_LIGHT, noiseLevel());
    analogWrite(PIR_LIGHT, motionLevel());
}