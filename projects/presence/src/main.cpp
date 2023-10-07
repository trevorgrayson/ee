//
// Created by trevor on 9/16/2023.
//
#include "Arduino.h"

#define PIR_PIN A0
#define MIC_PIN A1

void setup()
{
    Serial.begin(9600);
    pinMode(PIR_PIN, INPUT);
    pinMode(MIC_PIN, INPUT);
}

int noiseLevel()
{
    int reading = analogRead(MIC_PIN);
    return 10 - reading/100;
}

int motionLevel()
{
    int reading = analogRead(PIR_PIN);
    return reading > 10;
}

void loop()
{
    Serial.print(motionLevel());
    Serial.print("\t");
    Serial.print(noiseLevel());
    Serial.println();
}