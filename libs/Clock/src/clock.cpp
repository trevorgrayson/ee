//
// Created by trevor on 8/6/2023.
//

#include "clock.h"
#include <RTClib.h>
// #include <Wire.h>

RTC_DS3231 rtc;


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
}

int clockTimeDigits() {
    return rtc.now().hour() * 100 \
            + rtc.now().minute();
}

void adjust() {
    rtc.adjust(DateTime(2023, 8, 7, 20, 37, 0));
}