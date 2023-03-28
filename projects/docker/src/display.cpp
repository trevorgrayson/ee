//
// Created by trevor on 3/24/23.
//

#include "display.h"

#define CLK 12
#define DIO 14

TM1637Display display(CLK, DIO);


void initDisplay() {
    display.setBrightness(7, true);

}

void setDisplay(int distance) {
    display.showNumberDec(distance, false);
}
