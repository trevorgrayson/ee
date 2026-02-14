#include <Arduino.h>

#include "pins.h"
#include "console.h"


void setup()
{
    Serial.begin(9600);

    setupConsole();
    consolePrintLn("ready.");
}

void loop()
{

}
