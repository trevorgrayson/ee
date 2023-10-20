//
// Created by Trevor Grayson on 10/6/23.
//

#include "vent.h"
#include "pins.h"
#include <Arduino.h>

struct VentState {
    int tempurature;
    int radiation;    // negative impact to player
    double efficency; // to modify output
};

void setupVent()
{
    pinMode(VENT_BTN_1, INPUT_PULLUP);
    pinMode(VENT_BTN_2, INPUT_PULLUP);
    pinMode(VENT_BTN_3, INPUT_PULLUP);
}

int ventStatus(int ventNum)
{
    switch(ventNum) {
        case 0: return digitalRead(VENT_BTN_1);
        case 1: return digitalRead(VENT_BTN_2);
        case 2: return digitalRead(VENT_BTN_3);
    }
}

void tickVent(VentState state) // State *state) // input *state
{
    // reduce heat
    // radiate poison
    if (ventStatus(0)) {
        state.tempurature - 1;
    }
    if (ventStatus(1)) {
        state.tempurature - 5;
        state.radiation + 5;
    }
    if (ventStatus(2)) {
        state.tempurature - 10;
        state.radiation + 25;
    }

}