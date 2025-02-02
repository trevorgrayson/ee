//
// Created by trevor on 6/9/24.
//

#include "tm3.h"
#include "pins.h"
#include "clock.h"

// clock, dio
TM1637 lax(LAX1, LAX2);
TM1637 dia(DIA1, DIA2); // inverted
TM1637 nyc(NYC1, NYC2); // <=|

char buff[4];

void setuptm3()
{
    lax.init();
    dia.init();
    nyc.init();
    lax.setBrightness(0x01);
    dia.setBrightness(0x06);
    nyc.setBrightness(0x06);
}

void tm3alert()
{
    nyc.display("PAGE");
    dia.display("R  ");
    lax.display("DUTY");
}

void tm3display(int date)
{
    int offset = 0;
    if(date < 1000) offset = 1;
    if(date < 100) offset = 2;
    if(date < 10) offset = 3;

    lax.display(date, false, true, offset);
}

void tm3display()
{
    // display time
    // 4-digit LEDs
    nyc.display(timezone(clockTimeDigits(), 3), false, true);
    dia.display(timezone(clockTimeDigits(), 1), false, true);
    tm3display(clockTimeDigits());
}
