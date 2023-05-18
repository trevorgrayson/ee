#include <Arduino.h>
#include <Wire.h>
#include "display.h"

#define LED_PIN 2
#define SDA_PIN 2
#define SCL_PIN 0

void setup() {
    //pinMode(LED_PIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output

    Wire.pins(SDA_PIN, SCL_PIN);
    Wire.begin(SDA_PIN, SCL_PIN);        // join i2c bus (address optional for master)
    Serial.begin(9600);  // start serial for output
    delay(1000);
    Serial.print("start. ");
}

void loop() {
    Wire.requestFrom(0x5F, 6);    // request 6 bytes from peripheral device #8
    Serial.print(".");
    while (Wire.available()) { // peripheral may send less than requested
        char c = Wire.read(); // receive a byte as character
        Serial.print(c);         // print the character
        Serial.print("*");
//        Serial.print("*");

//        digitalWrite(LED_PIN, LOW);
//        delay(1000);
//        digitalWrite(LED_PIN, HIGH);
//        delay(1000);
    }

    delay(500);
}
// https://github.com/gamegine/HCSR04-ultrasonic-sensor-lib
