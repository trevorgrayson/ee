#include <Arduino.h>
#include "audio.h"
#include "dimmer.h"

#define LIGHT_SWITCH 12

int lights = 0;
bool debounce = 0;

void setup() {
    pinMode(LIGHT_SWITCH, INPUT);

    setupAudio();
    setupDimmer();
    Serial.begin(9600);
}

void loop() {
    tickAudio();

    switch(lights) {
        case 0: deluminate();
            break;
        case 1: illuminate();
            break;
        case 2: glow(0, 0, 255);
            break;
        case 3: glow(255, 0, 0);
            break;
//    case 4: glow(255, 0, 0);
//            break;
//    case 2: swirl();
//            break;
    }
    if(digitalRead(LIGHT_SWITCH) == HIGH & !debounce) {
        debounce = 1;
        lights = (lights + 1) % 4;
    } else if(digitalRead(LIGHT_SWITCH) == LOW) {
        debounce = 0;
    }

    delay(10);
}