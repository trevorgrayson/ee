//
// RGB Light dimmer by sliders, et al.
//
// Created by trevor on 10/2/2022.
//
#include "../include/dimmer.h"

#include "Arduino.h"

#define REDPIN    14  // A0, A1, A2
#define GREENPIN  15
#define BLUEPIN   16

#define FADESPEED 5     // make this higher to slow down

void setupDimmer() {
    pinMode(REDPIN, OUTPUT);
    pinMode(GREENPIN, OUTPUT);
    pinMode(BLUEPIN, OUTPUT);
}

void illuminate() {
    analogWrite(REDPIN, 255);
    analogWrite(GREENPIN, 255);
    analogWrite(BLUEPIN, 255);
}

void glow(int r, int g, int b) {
    analogWrite(REDPIN, r);
    analogWrite(GREENPIN, g);
    analogWrite(BLUEPIN, b);
}

void deluminate() {
    analogWrite(REDPIN, 0);
    analogWrite(GREENPIN, 0);
    analogWrite(BLUEPIN, 0);
}

void redAlert() {
    glow(255, 0, 0);
}

void swirl() {
    int r, g, b;

    // fade from blue to violet
    for (r = 0; r < 256; r++) {
        analogWrite(REDPIN, r);
        delay(FADESPEED);
    }
    // fade from violet to red
    for (b = 255; b > 0; b--) {
        analogWrite(BLUEPIN, b);
        delay(FADESPEED);
    }
    // fade from red to yellow
    for (g = 0; g < 256; g++) {
        analogWrite(GREENPIN, g);
        delay(FADESPEED);
    }
    // fade from yellow to green
    for (r = 255; r > 0; r--) {
        analogWrite(REDPIN, r);
        delay(FADESPEED);
    }
    // fade from green to teal
    for (b = 0; b < 256; b++) {
        analogWrite(BLUEPIN, b);
        delay(FADESPEED);
    }
    // fade from teal to blue
    for (g = 255; g > 0; g--) {
        analogWrite(GREENPIN, g);
        delay(FADESPEED);
    }
}
