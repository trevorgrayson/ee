//
// Created by trevor on 11/13/23.
//

#include "rotary.h"

#include <Arduino.h>
#include <RotaryEncoder.h>

#define PIN_IN1 A2
#define PIN_IN2 A3

RotaryEncoder *encoder = nullptr;

void checkPosition()
{
    encoder->tick(); // just call tick() to check the state.
}

void setupRotary() {
    encoder = new RotaryEncoder(PIN_IN1, PIN_IN2, RotaryEncoder::LatchMode::TWO03);

    // register interrupt routine
    attachInterrupt(digitalPinToInterrupt(PIN_IN1), checkPosition, CHANGE);
    attachInterrupt(digitalPinToInterrupt(PIN_IN2), checkPosition, CHANGE);
}

int tickRotary() {
    static int pos = 0;

    encoder->tick();

    int newPos = encoder->getPosition();
    // if (pos != newPos) {
    //     return newPos;
    //     // encoder->getDirection();
    // }

    return newPos;
}
