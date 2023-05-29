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

void loop() {
    tickBatteries();
}
