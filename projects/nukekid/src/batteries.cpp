//
// Created by trevor on 5/26/23.
//

#include "stdio.h"

#include "batteries.h"
#include "Arduino.h"
#include "pins.h"
#include "lcd.h"

#define BATT_COUNT 2

struct Battery {
    int pin;
    int charge;
    int desire;
};

Battery batts[BATT_COUNT];

char buff[] = "                \0";

void setupBatteries() {
    for (int batt=0; batt < BATT_COUNT; batt++) {
        batts[batt] = {0, 0, 0};
    }

    pinMode(BATT_SETTING_1, INPUT);
    pinMode(BATT_SETTING_2, INPUT);

    batts[0].pin = BATT_SETTING_1;
    batts[1].pin = BATT_SETTING_2;
}

int battSetting(int batt) {
    return analogRead(batts[batt].pin)/100;
}

void tickBatteries() {
    sprintf(buff, "B1: %2d B2: %2d",
            battSetting(0),
            battSetting(1));
    print(buff, 0);
}