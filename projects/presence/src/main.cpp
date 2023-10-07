//
// Created by trevor on 9/16/2023.
//
#include "Arduino.h"

#define PIR_PIN A0
#define MIC_PIN A1

#define PIR_LIGHT 13
#define MIC_LIGHT 9

void setup()
{
    Serial.begin(9600);
    pinMode(PIR_PIN, INPUT);
    pinMode(MIC_PIN, INPUT);

    pinMode(PIR_LIGHT, OUTPUT);
    pinMode(MIC_LIGHT, OUTPUT);
}

/*
 * return a 0-255 range
 */
int noiseLevel()
{
    int reading = analogRead(MIC_PIN);
    return 255 - (reading/4);
}

/*
 * return a 0-255 range
 */
int motionLevel()
{
    int reading = analogRead(PIR_PIN);
    return (reading / 600) * 255;
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