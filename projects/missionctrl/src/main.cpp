#include <Arduino.h>
// #include <TM1637Display.h>
#include <TM1637.h>
#include "clock.h"
#include "deej.h"
#include "console.h"
#include "pins.h"
#include "rotary.h"
#include "listen.h"

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
TM1637 lax(LAX1, LAX2);
TM1637 dia(DIA1, DIA2); // inverted
TM1637 nyc(NYC1, NYC2); // <=|


void alert()
{
    nyc.display("PAGE");
    dia.display("R  ");
    lax.display("DUTY");
}

void display()
{
    // display time
    // 4-digit LEDs
    nyc.display(timezone(clockTimeDigits(), 3));
    dia.display(timezone(clockTimeDigits(), 1));
    lax.display(clockTimeDigits());
}

void setup()
{
    Serial.begin(9600);

    clockSetup();
    setupDeej();
    setupConsole();
    setupRotary();
    // adjust(); // program the missionctrl

    // 4-digit LEDs
    lax.init();
    dia.init();
    nyc.init();
    lax.setBrightness(0x0a);
    dia.setBrightness(0x0a);
    nyc.setBrightness(0x0a);
    display();
}

void pomodoroButtonExecute() {
    alert();
    delay(1000);
    lax.display(date());
    setMeetingModulus();
    delay(1000);
}

void loop()
{
    clockTick();
    // tickDeej();
    // int rotaryPosition = tickRotary();
    // listen();

    display();
}
