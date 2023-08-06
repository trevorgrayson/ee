#include <Arduino.h>
#include <TM1637Display.h>


#include <RTClib.h>
// #include <Wire.h>

RTC_DS3231 rtc;

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

void clockSetup() {
    // initializing the rtc
    if(!rtc.begin()) {
        Serial.println("Couldn't find RTC!");
        Serial.flush();
        // while (1) delay(10);
    }

    if(rtc.lostPower()) {
        // this will adjust to the date and time at compilation
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }

    //we don't need the 32K Pin, so disable it
    rtc.disable32K();
}

void clockTick() {
    // print current time
    display.showNumberDec(rtc.now().hour()*100 + rtc.now().minute());
}


void setup()
{
    Serial.begin(9600);
    display.setBrightness(0x0a);

    clockSetup();
    // rtc.adjust(DateTime(2024, 8, 3, 1, 02, 0));
}

void loop()
{
    clockTick();
}