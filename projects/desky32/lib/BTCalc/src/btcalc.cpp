//
// Created by Trevor Grayson on 8/21/23.
//

#include "Arduino.h"
#include "btcalc.h"
#include <BleKeyboard.h>

#define SEND_PIN 13

BleKeyboard bleKeyboard("DeSKY", "tg.", 100);

// debounced send
int sendStateLast = 0;

void setupBTCalc() {
    bleKeyboard.begin();
    bleKeyboard.setBatteryLevel(100);
}

void setBTBatt(int level) {
    bleKeyboard.setBatteryLevel(level);
}

void btSend(double num) {
    bleKeyboard.print(num);
}

void btSend(char key) {
    bleKeyboard.print(key);
}

void btSendButton(double sendValue) {
    int sendReading = digitalRead(SEND_PIN);

    if (sendReading == LOW && sendStateLast == HIGH) {
        btSend(sendValue);
        delay(500);
        return;
    }

    if (sendReading != sendStateLast) {
        sendStateLast = sendReading;
    }
}
