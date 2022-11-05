#include <Arduino.h>
// #include "audio.h"
// #include "dimmer.h"
#include "serial.h"

void setup() {
    Serial.begin(115200);
    setupSerial();
}

void loop() {
    scanInput();
}