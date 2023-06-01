#include <Arduino.h>
#define CARDKB_ADDR 0x5F  //Define the I2C address of CardKB.
#include <Wire.h>

void setup() {
    Wire.begin();
    Serial.begin(9600);
    delay(1000);
    Serial.print("Start.");
}
void loop()
{
    Wire.requestFrom(CARDKB_ADDR, 1); //Request 1 byte from the slave device.
    while (Wire.available()) {
        char c = Wire.read();
        if (c != 0)
        {
            Serial.print(c);
        }
    }
}