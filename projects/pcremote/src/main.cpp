//
// Created by trevor on 7/8/2023.
//
// https://github.com/T-vK/ESP32-BLE-Keyboard
// https://support.google.com/a/users/answer/9896256?hl=en
// https://support.zoom.us/hc/en-us/articles/205683899-Hot-keys-and-keyboard-shortcuts

#include "Arduino.h"
#include <BleKeyboard.h>

#define PLAY_PAUSE T0 // push to talk
#define MIC_TOGGLE T8
#define VID_TOGGLE T9
// #define 6
// 9 10
// VIN GND
#define SUPER KEY_LEFT_GUI

//int LED_BUILTIN = 2;

BleKeyboard bleKeyboard("MeetingRemote", "ipsum");

const int threshold = 30;

void setup() {
    Serial.begin(9600);

//    pinMode(PLAY_PAUSE, INPUT_PULLUP);
//    pinMode(MIC_TOGGLE, INPUT_PULLUP);
//    pinMode(VID_TOGGLE, INPUT_PULLUP);
    pinMode(LED_BUILTIN, OUTPUT);

    bleKeyboard.begin();
}

int getButton(int pin) {
    return touchRead(pin) < threshold;
}

void loop() {
    digitalWrite(LED_BUILTIN, LOW);

    if(!bleKeyboard.isConnected()) {
        return;
    }
    Serial.println(touchRead(T0));
    Serial.println(touchRead(T1));
    Serial.println(touchRead(T2));
    Serial.println("===");

    if (getButton(PLAY_PAUSE)) {
        // space button
        bleKeyboard.write(' ');
        digitalWrite(LED_BUILTIN, HIGH);
        delay(1000);
    }
    return; // FOLLOWING PINS ALWAYS READING 0
            // FIND SAFE PINS

    if (getButton(MIC_TOGGLE)) {
        bleKeyboard.press(SUPER);
        bleKeyboard.press('e');
        delay(100);
        bleKeyboard.releaseAll();

        digitalWrite(LED_BUILTIN, HIGH);
        delay(1000);
    }
    if (getButton(VID_TOGGLE)) {
        bleKeyboard.press(SUPER);
        bleKeyboard.press('d');
        delay(100);
        bleKeyboard.releaseAll();

        digitalWrite(LED_BUILTIN, HIGH);
        delay(1000);
    }

    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
    // bleKeyboard.write(KEY_RETURN);
    // bleKeyboard.print("Hello world");
}