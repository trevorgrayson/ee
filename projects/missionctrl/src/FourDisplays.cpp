//
// Created by trevor on 1/25/26.
//

#include "FourDisplays.h"

// File: FourDisplays.h
#pragma once
#include <Wire.h>
#include "Adafruit_LEDBackpack.h"

class FourDisplays {
public:
    FourDisplays(uint8_t addrs[4]) {
        for (int i = 0; i < 4; i++) {
            addresses[i] = addrs[i];
            displays[i] = new Adafruit_7segment();
        }
    }

    void begin() {
        Wire.begin();
        for (int i = 0; i < 4; i++) {
            displays[i]->begin(addresses[i]);
            displays[i]->clear();
            displays[i]->writeDisplay();
        }
    }

    void show(int index, int value) {
        if (index < 0 || index >= 4) return;
        displays[index]->print(value);
        displays[index]->writeDisplay();
    }

    void show(int index, const char* str) {
        if (index < 0 || index >= 4) return;
        displays[index]->print(str);
        displays[index]->writeDisplay();
    }

    void clear(int index = -1) {
        if (index == -1) {
            for (int i = 0; i < 4; i++) {
                displays[i]->clear();
                displays[i]->writeDisplay();
            }
        } else if (index >= 0 && index < 4) {
            displays[index]->clear();
            displays[index]->writeDisplay();
        }
    }

private:
    Adafruit_7segment* displays[4];
    uint8_t addresses[4];
};
