#include <Arduino.h>
#include <TM1637Display.h>


//#define ONE_DAY  (24 * 60 * 60)
double ONE_DAY =  (24.0 * 60.0 * 60.0);
const uint8_t colonMask = 0b11100000;
const double MINUTES = 60.0;
const double HOURS = 3600.0;


// set the time
double epic = 21.0 *HOURS + 29.0 *MINUTES; // seconds

// Instantiation and pins configurations
// Pin 3 - > DIO
// Pin 2 - > CLK
TM1637Display display(2, 3);


double tick_epic = millis();


void setup()
{
    Serial.begin(9600);
    display.setBrightness(0x0a);
}

void loop()
{
    uint8_t toMask = 0b0;

    // Display Integers:
    double hours = floor(epic/3600.0);
    double minutes = floor((epic - (hours * 3600.0)) / 60.0);
    Serial.println(epic);
    Serial.println(hours);
    Serial.println(minutes);

    if (millis() - tick_epic > 1000) {
        tick_epic = millis();
        epic++;
        if (toMask) {
            toMask = 0b0;
        } else {
            toMask = colonMask;
        }

        display.showNumberDecEx(hours * 100.0 + minutes, toMask);
    }

    if (epic > ONE_DAY) {
        epic = 0000.0;
    }
}