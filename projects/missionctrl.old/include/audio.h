//
// Created by trevor on 10/2/2022.
//
#include "Arduino.h"

#ifndef EE_AUDIO_H
#define EE_AUDIO_H

const int NUM_SLIDERS = 3;
const int analogInputs[NUM_SLIDERS] = {A0, A1, A2};

int analogSliderValues[NUM_SLIDERS];


void updateSliderValues() {
    for (int i = 0; i < NUM_SLIDERS; i++) {
        analogSliderValues[i] = analogRead(analogInputs[i]);
    }
}

void sendSliderValues() {
    String builtString = String("");

    for (int i = 0; i < NUM_SLIDERS; i++) {
        builtString += String((int)analogSliderValues[i]);

        if (i < NUM_SLIDERS - 1) {
            builtString += String("|");
        }
    }

    Serial.println(builtString);
}

void printSliderValues() {
    for (int i = 0; i < NUM_SLIDERS; i++) {
        String printedString = String("Slider #") + String(i + 1) + String(": ") + String(analogSliderValues[i]) + String(" mV");
        Serial.write(printedString.c_str());

        if (i < NUM_SLIDERS - 1) {
            Serial.write(" | ");
        } else {
            Serial.write("\n");
        }
    }
}

void setupAudio() {
    for (int i = 0; i < NUM_SLIDERS; i++) {
        pinMode(analogInputs[i], INPUT);
    }
}

void tickAudio() {
    updateSliderValues();
    sendSliderValues(); // Actually send data (all the time)
    // printSliderValues(); // For debug
}
#endif //EE_AUDIO_H
