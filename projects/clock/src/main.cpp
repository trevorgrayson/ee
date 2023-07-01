#include <Arduino.h>
#include <TM1637.h>

#define ONE_DAY  (24 * 60 * 60)

const uint8_t colonMask = 0b01000000;

// Instantiation and pins configurations
// Pin 3 - > DIO
// Pin 2 - > CLK
TM1637 tm(2 , 15);

double epic = 12 * 3600 + 34 * 60; // seconds

void setup()
{
    tm.begin();
}

void loop()
{
    // Display Integers:
    int hours = floor(epic / 3600);
    int minutes = floor((epic - (hours * 3600)) / 60);

    tm.display(hours * 100 + minutes, colonMask);
    // display.showNumberDecEx(hourFormat12(timeinfo.tm_hour), colonMask, false, 2, upperDigits);
    epic++;
    if (epic > ONE_DAY) {
        epic = 0000;
    }
    delay(1000);
}