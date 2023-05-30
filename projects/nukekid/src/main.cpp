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

struct State {
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
    sprintf(buffCont, "Rod%2d %c Dep %2d", rodCurrent(), actuatorStatus(), rodDepth());
    print(buffCont, 0);
    sprintf(buffCont, "B1:>%2d Chg:%2d",
            battSetting(0), battCharge(0));
    print(buffCont, 1);
}

void battScreen() {
    sprintf(buffCont, "B1: %2d",
            battSetting(0));
    print(buffCont, 0);
}
void fuelRodScreen() {
    sprintf(buffCont, "Act: %c %4.2d",
            actuatorStatus(), rodButtonDepressed());
//    print(buff2, 1);
}

void loop() {
    tickBatteries();
    tickFuelRod();
    homeScreen();
    // controller.h to choose display
}
