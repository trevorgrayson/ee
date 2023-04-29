#include "calculator.h"
#include "keypad.h"


struct State {
    char buffer[50];
} state;


void setup()
{
    Serial.begin(9600);
}

void loop()
{
    char key = getKey();
    if(key) {
        calcPress(key);
    }
}
