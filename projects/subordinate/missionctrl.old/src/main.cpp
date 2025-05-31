#include <Arduino.h>
#include "../include/state.h"
// #include "audio.h"
#include "../include/dimmer.h"
#include "../include/serial.h"

#define RED_ALERT_BUTTON 13

struct State {
    int redAlert = 0;
    int r = 0;
    int g = 0;
    int b = 0;
} state;


int isRedAlert() {
    return digitalRead(RED_ALERT_BUTTON);
}

void updateState(State *state) {
    state->redAlert = isRedAlert();
}

void output(State state) {
    if(state.redAlert) {
        redAlert();
    } else {
        deluminate();
    }
}

void setup() {
    Serial.begin(115200);
    pinMode(RED_ALERT_BUTTON, INPUT);
    setupSerial();
}

void loop() {
    updateState(&state);
    output(state);
    // scanInput();
}