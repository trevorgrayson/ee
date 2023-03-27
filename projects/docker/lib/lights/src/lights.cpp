//
// Created by trevor on 1/8/23.
//
#include <Arduino.h>
#include "lights.h"

#define GREEN_PIN 7
#define YELLOW_PIN 8
#define RED_PIN 9

void setLights(int lights)
{
    digitalWrite(RED_PIN, LOW);
    digitalWrite(YELLOW_PIN, LOW);
    digitalWrite(GREEN_PIN, LOW);

    if(lights & 0b1) {

        digitalWrite(RED_PIN, HIGH);
    }
    if(lights & 0b10) {
        digitalWrite(YELLOW_PIN, HIGH);
    }
    if(lights & 0b100) {
        digitalWrite(GREEN_PIN, HIGH);
    }
}
