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


struct State {
    int temp;
};

void setup() {
    Serial.begin(115200);
    // hardware
    setupLCD();

    // custom
    setupBatteries();
    setupFuelRod();

    print("hello.");
    delay(200);
}

char buffCont[] = "                \0";

void homeScreen() {
    /*
     * Demand 4.2 Supply 0.1
     */
    sprintf(buffCont, "Draw%2d Pwr%3d", demand(), power());
    print(buffCont, 0);
//    print(buffCont, 1);
}

void battScreen() {
    sprintf(buffCont, "B1: Chg%2d/Cap:%2d",
            battCharge(0), battSetting(0));
    print(buffCont, 1);
}

void fuelRodScreen() {
    // sprintf(buffCont, "Act: %c %4.2d", actuatorStatus(), rodButtonDepressed());
    sprintf(buffCont, "Rod%2d %c Dep %2d", rodCurrent(), actuatorStatus(), rodDepth());
    print(buffCont, 1);
}

void loop() {
    tickBatteries();
    tickFuelRod();
    homeScreen();

    if (battChanged()) { // TODO: Fix battChanged() & mod on seconds
        battScreen();
        delay(500);  //TODO slows actuator when changing.
    } else {
        fuelRodScreen();
    }
    // controller.h to choose display
}
