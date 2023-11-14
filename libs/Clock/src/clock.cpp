//
// Created by trevor on 8/6/2023.
//

#include "clock.h"
#include "pomodoro.h"
#include <RTClib.h>
// #include <Wire.h>

#define UNIX2MINUTES 60; // TODO internet fact, needs citation.

RTC_DS3231 rtc;

int pomodoroMultiple = 0;
double pomodoroEpic = 0;

void clockSetup() {
    // initializing input button
    setupPomodoro();
    // initializing the rtc
    if(!rtc.begin()) {
        Serial.println("Couldn't find RTC!");
        Serial.flush();
        // while (1) delay(10);
    }

//    if(rtc.lostPower()) {
//        // this will adjust to the date and time at compilation
//        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
//    }

    //we don't need the 32K Pin, so disable it
    rtc.disable32K();
}

int clockTimeDigits() {
    return rtc.now().hour() * 100 \
            + rtc.now().minute();
}

void adjust() {
    rtc.adjust(DateTime(2023, 11, 13, 22, 57, 0));
}

int date() {
    return rtc.now().month() * 100 + rtc.now().day();
}

void pomodoroSetEpic() {
    pomodoroMultiple += 5;
    pomodoroEpic = rtc.now().unixtime() + pomodoroMultiple * UNIX2MINUTES;
}

int pomodoroTimeLeft() {
    int minutesLeft = (int)(pomodoroEpic - rtc.now().unixtime())/UNIX2MINUTES;

    if (minutesLeft <= 0) {
        pomodoroEpic = 0;
        pomodoroMultiple = 0;
    }
    return (int)max(minutesLeft, 0);
}

int timezone(int time, int offset) {
    // insert earliest time always
    // do not use negative offsets
    return (time + offset * 100) % 2400;
}



void decrementEpic() {

}

void clockTick() {
    // TODO library doesn't decrement `pomodoroMultiple`.
    if (pomodoroButtonPressed())
        pomodoroButtonExecute();

    pomodoroTick(rtc.now().minute());
}