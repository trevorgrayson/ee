#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_LEDBackpack.h>

class Multi7Seg {
public:
    Multi7Seg(uint8_t count = 4);

    bool begin(const uint8_t *addresses);
    void print(uint8_t index, int value);
    void clear(uint8_t index);
    void clearAll();

    void setBrightness(uint8_t brightness);

private:
    uint8_t _count;
    Adafruit_7segment *_displays;
};
