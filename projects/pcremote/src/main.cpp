//
// Created by trevor on 7/8/2023.
//
// https://github.com/T-vK/ESP32-BLE-Keyboard
// https://support.google.com/a/users/answer/9896256?hl=en
// https://support.zoom.us/hc/en-us/articles/205683899-Hot-keys-and-keyboard-shortcuts

#include "Arduino.h"
#include <BleKeyboard.h>

#define PLAY_PAUSE 12 // push to talk
#define MIC_TOGGLE 13
#define VID_TOGGLE 14
// #define 6
// 9 10
// VIN GND
#define SUPER KEY_LEFT_GUI
BleKeyboard bleKeyboard;

const int threshold = 16;

void setup() {
    pinMode(PLAY_PAUSE, INPUT_PULLUP);
    pinMode(MIC_TOGGLE, INPUT_PULLUP);
    pinMode(VID_TOGGLE, INPUT_PULLUP);

    bleKeyboard.begin();
}

int getButton(int pin) {
    return touchRead(pin) < threshold;
}

void loop() {
    if(!bleKeyboard.isConnected()) {
        return;
    }

    if (getButton(PLAY_PAUSE)) {
        // space button
        bleKeyboard.write(' ');
    }
    if (getButton(MIC_TOGGLE)) {
        bleKeyboard.press(SUPER);
        bleKeyboard.press('e');
        delay(100);
        bleKeyboard.releaseAll();
    }
    if (getButton(VID_TOGGLE)) {
        bleKeyboard.press(SUPER);
        bleKeyboard.press('d');
        delay(100);
        bleKeyboard.releaseAll();
    }

    // bleKeyboard.write(KEY_RETURN);
    // bleKeyboard.print("Hello world");
}