//
// Created by trevor on 8/8/2023.
//

#include "deej.h"
#include <Arduino.h>

#define A0 14
#define A1 15
#define A2 16

const int NUM_SLIDERS = 3;
const int analogInputs[NUM_SLIDERS] = {A0, A1, A2}; // , A3, A4};

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

void setupDeej() {
    for (int i = 0; i < NUM_SLIDERS; i++) {
        pinMode(analogInputs[i], INPUT);
    }

    // Serial.begin(9600);
}

void tickDeej() {
    updateSliderValues();
    sendSliderValues(); // Actually send data (all the time)
    // printSliderValues(); // For debug
    delay(10);
}
