
#include "Arduino.h"
#include "kbd.h"
#include "Wire.h"

char inputBuffer[10000] = {};
int offset = 0;

void flushBuffer()
{
    for (char * c = inputBuffer;
    c != inputBuffer + sizeof(inputBuffer) / sizeof(inputBuffer[0]);
    ++c) {
        Wire.write(c);
    }
}

void setup()
{
    setupKbd();

    Wire.begin(0x5f);
    Wire.onRequest(flushBuffer);
}

void loop()
{
    tickKbd();
    char key = getKey();
    if (key) {
        inputBuffer[offset] = key;
        key = 0;

        flashOn();
        delay(100);
        flashOff();
    }
}