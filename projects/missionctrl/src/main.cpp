#include <Arduino.h>
// #include <TM1637Display.h>
#include "clock.h"
//#include "deej.h"
//#include "console.h"
#include "pins.h"
#include "rotary.h"
//#include "listen.h"
#include "tm3.h"


uint8_t dispAddrs[4] = {0x70, 0x71, 0x72, 0x73};

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

/*******
 * event triggers
 */
void pomodoroButtonExecute() {
    tm3alert();

    tm3display(date());
    setMeetingModulus();
    delay(1000);
}

void setup()
{
    Serial.begin(9600);
    // 4-digit LEDs
    Serial.println("begin...");
    setuptm3(); Serial.println("tm3 setup... [ OK ]");
    //clockSetup(2025, 10, 19, 9, 17);
    clockSetup(); Serial.println("RTC setup... [ OK ]");
    delay(500);

    setupRotary();
}

void loop()
{
    clockTick();
    tm3display();
    int newMinutes = tickRotary();
    if (newMinutes > -1000)
    {
        Serial.print("Minutes set:");
        Serial.println(newMinutes);
        // adjustMinutes(newMinutes);
    }
}
