#include <Arduino.h>
#include <TM1637Display.h>
#include "clock.h"
#include "deej.h"

//#define ONE_DAY  (24 * 60 * 60)
double ONE_DAY =  (24.0 * 60.0 * 60.0);
const uint8_t colonMask = 0b11100000;
const double MINUTES = 60.0;
const double HOURS = 3600.0;


// set the time
double epic = 9.0 *HOURS + 21.0 *MINUTES; // seconds

// Instantiation and pins configurations
// Pin 3 - > DIO
// Pin 2 - > CLK
TM1637Display lax(2, 3);
TM1637Display dia(4, 5);
TM1637Display nyc(6, 7);

void setup()
{
    Serial.begin(9600);

    clockSetup();
    setupDeej();
    // adjust(); // program the clock

    // 4-digit LEDs
    lax.setBrightness(0x0a);
    dia.setBrightness(0x0a);
    nyc.setBrightness(0x0a);

}

void loop()
{
    clockTick();
    tickDeej();

    // 4-digit LEDs
    nyc.showNumberDec(timezone(clockTimeDigits(), 3));
    dia.showNumberDec(timezone(clockTimeDigits(), 1));
    lax.showNumberDec(clockTimeDigits());
}