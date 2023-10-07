//
// Created by trevor on 5/26/23.
// QA'ed 2023/10/05

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
    int durability;
    int depth;
};

int presentRod = 0; // location
int displacement = 0; // moving between rods

Rod rods[ROD_COUNT];

char buff2[] = "                \0";

void setupFuelRod() {
    for (int rod=0; rod < ROD_COUNT; rod++) {
        rods[rod] = {rod, 5, 0};
    }

    // setup pins
    pinMode(ARTICULATE_SWITCH_UP, INPUT_PULLUP);
    pinMode(ARTICULATE_SWITCH_DOWN, INPUT_PULLUP);
    pinMode(ROD_SELECT, INPUT_PULLUP);
}

/*
 *
 */
int rodCurrent() {
    return rods[presentRod].durability * rods[presentRod].depth;
}

int rodDepth() {
    return rods[presentRod].depth;
}

int nextRod() {
    presentRod++;

    if (presentRod > ROD_COUNT - 1)
        presentRod = 0;

    return presentRod;
}

int rodSelection() {
    return rods[presentRod].num;
}

int actuatorStatus() {
    if (digitalRead(ARTICULATE_SWITCH_UP) == 0) {
        return 85;
    } else if (digitalRead(ARTICULATE_SWITCH_DOWN) == 0) {
        return 68;
    }
    return 20;
}

int rodButtonDepressed() {
    return digitalRead(ROD_SELECT) == 0;
}

int rodLift(int dist) {
    return 1;
}

int power() {
    int power = 0;
    for(int rod=0; rod< ROD_COUNT; rod++) {
        Rod rodney = rods[rod];
        power += rodney.durability * rodney.depth * 1;
    }

    return power;
}

void tickFuelRod() {
    Rod rod = rods[presentRod];

    int actuator = actuatorStatus();
    switch(actuator) {
        case 85:
            if(rod.depth > 0)
                rods[presentRod].depth -= 1;
            break;
        case 68:
            if(rod.depth < 70)
                rods[presentRod].depth += 1;
            break;
    }

    // TODO needs debouncing
    if (rodButtonDepressed())
        nextRod();

}