//
// Created by trevor on 3/24/23.
//

#include "display.h"

#define CLK 7
#define DIO 8

TM1637Display display(CLK, DIO);


void initDisplay() {
    display.setBrightness(0x0f);

}

void setDisplay(int distance) {
    display.showNumberDec(0, false);
}
