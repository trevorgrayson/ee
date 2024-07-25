#include <Arduino.h>
// #include <TM1637Display.h>
#include "clock.h"
#include "deej.h"
#include "console.h"
#include "pins.h"
#include "rotary.h"
#include "listen.h"
#include "tm3.h"

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


void pomodoroButtonExecute() {
    tm3alert();
    delay(1000);
    lax.display(date());
    setMeetingModulus();
    delay(1000);
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
    setuptm3();
    tm3display();
}

void loop()
{
    clockTick();
    // tickDeej();
    // int rotaryPosition = tickRotary();
    // listen();

    tm3display();
}
