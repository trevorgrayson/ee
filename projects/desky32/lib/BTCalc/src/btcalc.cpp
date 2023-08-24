//
// Created by Trevor Grayson on 8/21/23.
//

#include "btcalc.h"
#include <BleKeyboard.h>

BleKeyboard bleKeyboard("DeSKY", "tg.", 100);


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
