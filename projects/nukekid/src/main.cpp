/*********

  Batteries 2x
  - setting knob
  - 10 segment display

  Rod Management
  - up/down articulator
  - Rod Selector

  Venting 3x - low, mid, high
  - button
  - light indicator

*********/

#include <Arduino.h>
#include "lcd.h"
#include "fuelrod.h"
#include "batteries.h"
#include "grid.h"
#include "controller.h"
#include "vent.h"

#define DEBUG true

struct State {
    int power;
    int gridDraw;
    int tempurature;
    int radiation;
    double efficency;
};

State state = {0, 0, 0, 0, 1};

void setup() {
    Serial.begin(9600);
    // hardware
    setupLCD();

    // custom
    setupBatteries();
    setupFuelRod();
    setupVent();

    pinMode(OUTPUT, 25);
    pinMode(OUTPUT, 26);
    Serial.println("KoW Industries");
}

void debug() {
    Serial.print(rodSelection());
    Serial.print("\t");
    Serial.print(rodDepth());
    Serial.print("\t");
    Serial.print(rodCurrent());
    Serial.print("\t");
    Serial.print(power());
    //Serial.println();

    Serial.print(ventStatus(-1));
    Serial.print("\t");
    Serial.print(ventStatus(0));
    Serial.print("\t");
    Serial.print(ventStatus(1));
    Serial.print("\t");
    Serial.println();
}

void kidMode() {

}


void loop() {

    // READ
    // switch
    // fuel rod btn
    // vent btns
    // batt setting

}

void loop() {
    // Update
    tickBatteries();  // batt info stored in module
    tickFuelRod();    // stores rod info
    // tickVent();




    if (DEBUG) {
        debug();
    }
    return;
    // read
    state.power = power();
    state.gridDraw = demand();

    // debug
    // setBatt(0, 255);
    // setBatt(1, 255);

    int available = state.power - state.gridDraw;

    int draw = state.gridDraw + battDraw(available);
    int totalPower = state.power + battDistribute(state.gridDraw);

    // Visualize
    homeScreen(draw, state.power);

    if (battChanged()) { // TODO: Fix battChanged() & mod on seconds
        battScreen(battCharge(0), battSetting(0));
        delay(500);  //TODO slows actuator when changing.
    } else {
        fuelRodScreen(rodCurrent(), actuatorStatus(), rodDepth());
    }
    battDisplay();

}
