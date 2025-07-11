//
// Created by trevor on 6/9/24.
//
#include <stdio.h>
#include <TM1637Display.h>
#include "tm3.h"
#include "pins.h"
#include "clock.h"

// clock, dio
TM1637Display  lax(LAX1, LAX2);
TM1637Display  nyc(NYC1, NYC2);
TM1637Display  dia(DIA1, DIA2); // non chronological?

int offset = 0; // <== huh?!

void setuptm3()
{
    lax.setBrightness(1);
    nyc.setBrightness(1);
}

void tm3alert()
{
}

void random(int date)
{

}

void tm3display(int date)
{
    lax.showNumberDec(date, true);
}

void tm3display(int date, int device_idx)
{
    TM1637Display *device;

    switch (device_idx) {
        case 0: device = &lax; break;
        case 1: device = &nyc; break;
        // case 2: device = &dia; break;
    }
}

void tm3display()
{
    nyc.showNumberDec(clockTimeDigitsForTZ(IST), true);
    lax.showNumberDec(clockTimeDigitsForTZ(LAX), true);
    // lax.switchColon();
}
