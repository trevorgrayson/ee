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

    //    nyc.display("RULZ");
    //    lax.display("IZZY");
}

void tm3alert()
{
//    lax.setFloatDigitCount("HELi");
//    nyc.setFloatDigitCount("IZZY");
}

void tm3display(int date)
{
//    lax.display(date, false, true, offset);
//    lax.colonOn();
}

void random(int date)
{
    int offset = 0;
    if(date < 1000) offset = 1;
    if(date < 100) offset = 2;
    if(date < 10) offset = 3;

//    nyc.display(date, false, true, offset);
//    lax.colonOn();
}

void tm3display(int date, int device_idx)
{
    TM1637Display *device;

    switch (device_idx) {
        case 0: device = &lax; break;
        // case 1: device = &dia; break;
        case 2: device = &nyc; break;
    }

//    device->display(date, false, true, offset);
//    device->colonOn();
}

void tm3display()
{
    // display time
    // 4-digit LEDs

    nyc.showNumberDec(clockTimeDigitsForTZ(IST), true);
    lax.showNumberDec(clockTimeDigitsForTZ(LAX), true);
    // lax.switchColon();
}
