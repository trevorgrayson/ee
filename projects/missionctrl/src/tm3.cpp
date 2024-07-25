//
// Created by trevor on 6/9/24.
//

#include "tm3.h"
#include "pins.h"
#include "clock.h"



void setuptm3()
{
    lax.init();
    dia.init();
    nyc.init();
    lax.setBrightness(0x0a);
    dia.setBrightness(0x0a);
    nyc.setBrightness(0x0a);
}

void tm3alert()
{
    nyc.display("PAGE");
    dia.display("R  ");
    lax.display("DUTY");
}

void tm3display()
{
    // display time
    // 4-digit LEDs
    nyc.display(timezone(clockTimeDigits(), 3));
    dia.display(timezone(clockTimeDigits(), 1));
    lax.display(clockTimeDigits());
}
