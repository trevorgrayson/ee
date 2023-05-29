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
    pinMode(ARTICULATE_SWITCH_UP, INPUT);
    pinMode(ARTICULATE_SWITCH_DOWN, INPUT);
    pinMode(ROD_SELECT, INPUT);

    batts[0].pin = BATT_SETTING_1;
    batts[1].pin = BATT_SETTING_2;
}

void tickBatteries() {
    sprintf(buff, "Batt1: %4.2d",
            analogRead(BATT_SETTING_1));
    print(buff, 0);
    sprintf(buff, "Batt2: %4.2d",
            analogRead(BATT_SETTING_2));
    print(buff, 1);
}