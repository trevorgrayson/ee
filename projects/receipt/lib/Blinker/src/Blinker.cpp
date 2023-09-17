//
// Created by trevor on 9/16/2023.
//

#include "Arduino.h"
#include "Blinker.h"

#define LED_PIN 2

void blinkerSetup()
{
    pinMode(LED_PIN, OUTPUT);
}

void blink(unsigned int time, unsigned int count) {
    for (unsigned int x=0; x < count; x++) {
        digitalWrite(LED_PIN, LOW);
        delay(time);
        digitalWrite(LED_PIN, HIGH);
        delay(time);
    }
}

void blink(unsigned int time) {
    blink( time, 2);
}
