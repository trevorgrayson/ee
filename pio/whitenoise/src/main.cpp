// https://github.com/simonmonk/arduino_TEA5767/blob/master/examples/SimpleFixedFrequency/SimpleFixedFrequency.ino
#include <Arduino.h>
#include <Wire.h>
#include <TEA5767Radio.h>

TEA5767Radio radio = TEA5767Radio();

void setup()
{
    Wire.begin();
    radio.setFrequency(93.0); // pick your own frequency
}

void loop()
{
}