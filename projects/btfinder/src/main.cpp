/**************************************************************************
 * BTFinder
 * Estimated range to paired device.
 *
 * TODO
 * ====
 * Change to BT device, or add BT module
 * BT
     * pairing
     * fulfill BT requirements in `rangefinder.h` module
 * display.h works
 * display results
 *
 * Also, pezo beeping could be better.
 **************************************************************************/

#include <Arduino.h>
// #include "display.h"
#include "rangefinder.h"
#include <stdio.h>

char buff[50];
int range = 0;

// Move to Lib
void print()
{   // Fulfilled in ../libs/Display1306
    Serial.println(buff);
}

// start
void printRange(int range)
{
    Serial.println(buff);
    sprintf(buff, "OK");
    print();
}

void setup() {
    Serial.begin(9600);
    // displaySetup();

    Serial.println("Start.");
}

void loop() {
    range = getRange();
    printRange(range);

    delay(500);
}