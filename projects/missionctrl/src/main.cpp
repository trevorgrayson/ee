#include <Arduino.h>

#include "pins.h"
#include "console.h"
#include "listen.h"
#include <Multi7Seg.h>

uint8_t addresses[] = { 0x70, 0x71, 0x72, 0x73 }; //

Multi7Seg displays(1);

void setup()
{
    Serial.begin(115200);
    Serial1.begin(115200);

    setupConsole();
    consolePrintLn("ready.");
    consoleLightOn();

    displays.begin(addresses);
    displays.setBrightness(5);
}

void loop()
{
    listen();
    consolePrintLn("ok", 3);

    static int counter = 1;

    displays.print(0, counter);
//    displays.print(1, counter + 1);
//    displays.print(2, counter + 2);
//    displays.print(3, counter + 3);

    counter++;

    delay(500);
}
