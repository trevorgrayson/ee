//
// Created by trevor on 11/24/2023.
//

#include "presence.h"

#include "Arduino.h"
#include "pins.h"
#include "presenceState.h"

struct Presence presence = {0, 0};

void setupPresence()
{
    Serial.begin(9600);
    pinMode(PIR_PIN, INPUT);
    pinMode(MIC_PIN, INPUT);

    pinMode(PIR_LIGHT, OUTPUT);
    pinMode(MIC_LIGHT, OUTPUT);

    presence.noiseLevel = 0;
    presence.motionLevel = 0;
}

/*
 * return a 0-255 range
 */
int noiseLevel()
{
    int reading = analogRead(MIC_PIN);
    return reading; // 255 - (reading/4);
}

/*
 * return a 0-255 range
 */
int motionLevel()
{
    int reading = analogRead(PIR_PIN);
    return reading; // (reading / 600) * 255;
}

struct Presence *presenceState()
{
    presence.noiseLevel = noiseLevel();
    presence.motionLevel = motionLevel();
    return &presence;
}
