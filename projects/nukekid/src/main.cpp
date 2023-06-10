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


struct State {
    int power;
    int gridDraw;
    int temp;
};

State state = {0, 0, 0};

void setup() {
    Serial.begin(115200);
    // hardware
    setupLCD();

    // custom
    setupBatteries();
    setupFuelRod();

    print("KoW Industries");
    delay(200);
}

void loop() {
    // Update
    tickBatteries();
    tickFuelRod();

    state.power = power();
    state.gridDraw = demand();

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
    battDisplay(0);
}
