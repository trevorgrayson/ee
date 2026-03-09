#include <Arduino.h>

#include "pins.h"
#include "console.h"
#include "listen.h"
#include <Multi7Seg.h>
#include "clock.h"

uint8_t addresses[] = { 0x70, 0x74,  0x72, 0x71 }; //

Multi7Seg displays(4);
// Console LCD

void pomodoroButtonExecute() {
}


void scani2c() {
    byte error, address;
    int devices = 0;

    Serial.println("Scanning...");

    for (address = 1; address < 127; address++) {
        Wire.beginTransmission(address);
        error = Wire.endTransmission();

        if (error == 0) {
            Serial.print("I2C device found at 0x");
            if (address < 16)
                Serial.print("0");
            Serial.println(address, HEX);

            devices++;
        }
    }

    if (devices == 0)
        Serial.println("No I2C devices found\n");
    else
        Serial.println("Done\n");

    delay(5000);
}

void setup()
{
    Serial.begin(115200);
    Serial1.begin(115200);

    setupConsole();
    consolePrintLn("ready.");
    consoleLightOff();

    clockSetup(2026, 3, 9, 7, 35); Serial.println("RTC setup... [ OK ]");

    displays.begin(addresses);
    displays.setBrightness(5);

    // detect peripherals.
    scani2c();
}

void loop()
{
//    listen();
//    consolePrintLn("ok");
//    consolePrintLn("ok", 1);

    static int counter = 1;

    displays.print(0, clockTimeDigitsForTZ(LAX));
    displays.print(1, clockTimeDigitsForTZ(IST));
//    displays.print(2, counter + 2);
//    displays.print(3, counter + 3);

    counter++;

    delay(500);
}
