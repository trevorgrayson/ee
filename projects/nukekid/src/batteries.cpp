//
// Created by trevor on 5/26/23.
//

#include "stdio.h"

#include "batteries.h"
#include "Arduino.h"
#include "pins.h"
#include "lcd.h"

#define BATT_COUNT 2
#define MAX_DISBURSE 10
#define MAX_CHARGE 10

struct BattState {
    int dirty;
    struct Battery *batts[];
};

struct Battery {
    int pin;
    int charge;
    int desire;

    int dirty;
};

Battery batts[BATT_COUNT];
BattState battState;

char buff[] = "                \0";

void setupBatteries() {
    for (int batt=0; batt < BATT_COUNT; batt++) {
        batts[batt] = {0, 1, 0, 0};
    }

    pinMode(BATT_SETTING_1, INPUT);
    pinMode(BATT_SETTING_2, INPUT);

    batts[0].pin = BATT_SETTING_1;
    batts[1].pin = BATT_SETTING_2;
}

int battSetting(int batt) {
    batts[batt].desire = analogRead(batts[batt].pin)/100;
    return batts[batt].desire;
}

int battCharge(int batt) {
    return batts[batt].charge;
}

/*
 * Calculate the Battery's Draw
 */
int battDraw(int availablePower) {
    int draw = 0;
    for (int x = 0; x<BATT_COUNT; x++) {
        int charge = max(0, batts[x].charge);

        if (batts[x].desire > charge) {
            batts[x].charge = min(availablePower,
                                  min(MAX_CHARGE, charge + 1)); // TODO 1?
            draw = draw + charge;
        }

    }

    return draw;
}

int battDistribute(int draw) {
    int charge = batts[0].charge;

    if( charge < 1 ||
        batts[0].desire >= charge)
        return 0;

    int output = min(min(MAX_DISBURSE, draw), charge);
    output = min(output, charge - output);
    batts[0].charge = charge - output;

    return output;
}

void tickBatteries() {
    for (int batt=0; batt < BATT_COUNT; batt++) {
        int desire = battSetting(batt);
        batts[batt].dirty = abs(desire) - abs(batts[batt].desire) < 2 ? 1 : 0;
        batts[batt].desire = desire;
    }
}

int battChanged() {
   return batts[0].dirty;
}