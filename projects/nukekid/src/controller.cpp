//
// Created by trevor on 5/29/23.
//

#include "controller.h"

#include <stdio.h>
#include "lcd.h"

char buffCont[17];

/*
 * Demand 4.2 Supply 0.1
 */
void homeScreen(int draw, int pwr) {
    sprintf(buffCont, "Draw%2d Pwr%3d", draw, pwr);
    print(buffCont, 0);
//    print(buffCont, 1);
}

void battScreen(int battCharge, int battSetting) {
    sprintf(buffCont, "B1: Chg%2d/Cap:%2d",
            battCharge, battSetting);
    print(buffCont, 1);
}

void fuelRodScreen(int rodCurrent, int actuatorStatus, int rodDepth) {
    // sprintf(buffCont, "Act: %c %4.2d", actuatorStatus(), rodButtonDepressed());
    sprintf(buffCont, "Rod%2d %c Dep %2d", rodCurrent, actuatorStatus, rodDepth);
    print(buffCont, 1);
}

void controller() {

}