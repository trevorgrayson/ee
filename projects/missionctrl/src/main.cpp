#include <Arduino.h>
#include <TM1637Display.h>
#include "clock.h"
#include "deej.h"
#include "console.h"
#include "pins.h"
#include "terminal.h"
#include "rotary.h"

//#define ONE_DAY  (24 * 60 * 60)
double ONE_DAY =  (24.0 * 60.0 * 60.0);
const uint8_t colonMask = 0b11100000;
const double MINUTES = 60.0;
const double HOURS = 3600.0;

// set the time
double epic = 9.0 *HOURS + 21.0 *MINUTES; // seconds

char buffer[20];
// Instantiation and pins configurations
// Pin 3 - > DIO
// Pin 2 - > CLK
TM1637Display lax(LAX1, LAX2);
TM1637Display dia(DIA1, DIA2); // inverted
TM1637Display nyc(NYC1, NYC2); // <=|

void setup()
{
    Serial.begin(9600);

    clockSetup();
    setupDeej();
    setupConsole();
    setupRotary();
    // adjust(); // program the missionctrl

    // 4-digit LEDs
    lax.setBrightness(0x0a);
    dia.setBrightness(0x0a);
    nyc.setBrightness(0x0a);
}

void pomodoroButtonExecute() {
    lax.showNumberDec(date());
    setMeetingModulus();
    delay(1000);
}

void loop()
{
    char first;

    clockTick();
    tickDeej();
    int rotaryPosition = tickRotary();

    String line = terminalReceive();
    if (line) {
        first = line.charAt(0);
        line.toCharArray(buffer, 20);

        switch (first) {
            case '!':
                // increment elecromag counter
                break;
            case '0':
                consolePrintLn(buffer, 0);
            case '1':
                consolePrintLn(buffer, 1);
            case '2':
                consolePrintLn(buffer, 2);
            case '3':
                consolePrintLn(buffer, 3);
            default:
                consolePrintLn(buffer);
        }
    }

    int timeLeft = pomodoroTimeLeft();

    // conditional LED view.
    if (false) { // timeLeft > 0) {
        // TODO:
        nyc.showNumberDec(pomodoroTimeLeft());
        dia.showNumberDec(timezone(clockTimeDigits(), 1));
        lax.showNumberDec(date());
    } else {
        // display time
        // 4-digit LEDs
        nyc.showNumberDec(timezone(clockTimeDigits(), 3));
        dia.showNumberDec(timezone(clockTimeDigits(), 1));
        lax.showNumberDec(clockTimeDigits());
    }

}
