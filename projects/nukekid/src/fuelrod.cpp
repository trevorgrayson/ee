//
// Created by trevor on 5/26/23.
//

#include "../include/fuelrod.h"
#include "Arduino.h"
#include "pins.h"
#include "lcd.h"

#define ROD_COUNT 3

#define ROD_LENGTH 100
#define ROD_STEP 1

#define TRAVEL_TIME 100
#define TRAVEL_STEP 1

struct Rod {
    int num;
    int depth;
};

int presentRod = 0; // location
int displacement = 0; // moving between rods

Rod rods[ROD_COUNT];

void setupFuelRod() {
    for (int rod=0; rod < ROD_COUNT; rod++) {
        rods[rod] = {rod, 0};
    }

    // setup pins
    pinMode(ARTICULATE_SWITCH_UP, INPUT_PULLUP);
    pinMode(ARTICULATE_SWITCH_DOWN, INPUT_PULLUP);
    pinMode(ROD_SELECT, INPUT_PULLUP);
}

int nextRod() {
    return presentRod++;
}

int actuatorStatus() {
    if (digitalRead(ARTICULATE_SWITCH_UP) == 1) {
        return 1;
    } else if (digitalRead(ARTICULATE_SWITCH_DOWN) == 1) {
        return -1;
    }

    return 0;
}

int rodLift(int dist) {
    return 1;
}

void tickFuelRod() {
}