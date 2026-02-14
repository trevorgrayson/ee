//
// Created by trevor on 11/13/23.
//

#include "rotary.h"

#include <Arduino.h>
#include <RotaryEncoder.h>
#include "pins.h"
#include "clock.h"

RotaryEncoder *smallKnob = nullptr;
RotaryEncoder *largeKnob = nullptr;



int tickRotary() {
    // TODO split out each encoder to a function
    static int smPos = smallKnob->getPosition();
    static int lgPos = 0;
    smallKnob->tick();

    int newSmPos = smallKnob->getPosition();
    if (smPos != newSmPos) {
        int smDiff = newSmPos-smPos;
        smPos = smDiff;
        // smallKnob->getDirection();
        return smDiff;
    } else {
        return -10000;
    }

//    largeKnob->tick();
//
//    int newLgPos = largeKnob->getPosition();
//    if (lgPos != newLgPos) {
//        Serial.println(newLgPos-smPos);
//        adjustHours(newLgPos-smPos);
//        largeKnob->getDirection();
//    }


}

void setupRotary() {
    pinMode(ENCODER_SM_PIN1, INPUT_PULLUP);
    pinMode(ENCODER_SM_PIN2, INPUT_PULLUP);
    smallKnob = new RotaryEncoder(ENCODER_SM_PIN1, ENCODER_SM_PIN2, RotaryEncoder::LatchMode::TWO03);

    pinMode(ENCODER_LG_PIN1, INPUT_PULLUP);
    pinMode(ENCODER_LG_PIN2, INPUT_PULLUP);
    largeKnob = new RotaryEncoder(ENCODER_LG_PIN1, ENCODER_LG_PIN2, RotaryEncoder::LatchMode::TWO03);

    // register interrupt routine
    // only pins 2, 3 work on uno
    // atmega32u4  2, 3, 18, 19, 20, 21
//    attachInterrupt(digitalPinToInterrupt(ENCODER_SM_PIN1), tickRotary, CHANGE);
//    attachInterrupt(digitalPinToInterrupt(ENCODER_SM_PIN2), tickRotary, CHANGE);
//    attachInterrupt(digitalPinToInterrupt(ENCODER_LG_PIN1), tickRotary, CHANGE);
//    attachInterrupt(digitalPinToInterrupt(ENCODER_LG_PIN2), tickRotary, CHANGE);
}