#include <Arduino.h>
#include <TM1637.h>

const uint8_t colonMask = 0b01000000;

// Instantiation and pins configurations
// Pin 3 - > DIO
// Pin 2 - > CLK
TM1637 tm(2, 3);

void setup()
{
    tm.begin();
}

void loop()
{
    // Display Integers:
    tm.display(1234, colonMask);
    // display.showNumberDecEx(hourFormat12(timeinfo.tm_hour), colonMask, false, 2, upperDigits);
    delay(1000);
}