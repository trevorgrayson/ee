//
// Created by trevor on 8/6/2023.
//

#include "clock.h"
#include "pomodoro.h"
#include <RTClib.h>
#include <Timezone.h> // e.g. https://github.com/JChristensen/Timezone/blob/master/examples/HardwareRTC/HardwareRTC.ino

#define UNIX2MINUTES 60; // TODO internet fact, needs citation.

TimeChangeRule myDST = {"EDT", Second, Sun, Mar, 2, -60 * 4};    //Daylight time = UTC - 4 hours
TimeChangeRule mySTD = {"EST", First, Sun, Nov, 2,  -60 * 5};     //Standard time = UTC - 5 hours
Timezone JFK_TZ(myDST, mySTD);

TimeChangeRule edt = {"PDT", Second, Sun, Mar, 2,   -420};
TimeChangeRule est = {"PST", First, Sun, Nov, 2,    -480};
Timezone LAX_TZ(edt, est);

TimeChangeRule idt = {"IST", First, Sun, Nov, 2,    +330};
TimeChangeRule ist_ = {"IST", Second, Sun, Nov, 2,    +330};
Timezone IST_TZ(idt, ist_);

RTC_DS3231 rtc;

int pomodoroMultiple = 0;
double pomodoroEpic = 0;

int clockTimeDigits() {
    return rtc.now().hour() * 100 \
            + rtc.now().minute();
}

int clockTimeDigitsForTZ(int tz)  {
    DateTime now = rtc.now();
    time_t utc = now.unixtime();

    time_t local = LAX_TZ.toLocal(utc);
    if(tz == JFK) local = JFK_TZ.toLocal(utc);
    else if (tz == IST) local = IST_TZ.toLocal(utc);

    return hour(local) * 100 + minute(local);
}

void printTime(time_t t) {
    char buf[20];
    sprintf(buf, "%04d-%02d-%02d %02d:%02d:%02d",
            year(t), month(t), day(t),
            hour(t), minute(t), second(t));
    Serial.println(buf);
}

// month day minute
int unixtime() {
    return rtc.now().unixtime();
}

void adjust() {
//    rtc.adjust(DateTime(2025, 07, 10, 19, 46, 30)); // UTC
    rtc.adjust(DateTime(2025, 10, 16, 8, 3, 00)); // UTC
//    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void adjustHours(int num)
{
    DateTime now = rtc.now();
    rtc.adjust(DateTime(
            rtc.now().year(),
            rtc.now().month(),
            rtc.now().day(),
            rtc.now().hour() + num,
            rtc.now().minute(),
            rtc.now().second()
    ));
}

void adjustMinutes(int num)
{
    DateTime now = rtc.now();
    rtc.adjust(DateTime(
        rtc.now().year(),
        rtc.now().month(),
        rtc.now().day(),
        rtc.now().hour(),
        rtc.now().minute() + num,
        rtc.now().second()
    ));
}

int date() {
    return (rtc.now().month() * 100) + rtc.now().day();
}

void pomodoroSetEpic() {
    pomodoroMultiple += 5;
    pomodoroEpic = unixtime() + pomodoroMultiple * UNIX2MINUTES;
}

int pomodoroTimeLeft() {
    int minutesLeft = (int)(pomodoroEpic - unixtime())/UNIX2MINUTES;

    if (minutesLeft <= 0) {
        pomodoroEpic = 0;
        pomodoroMultiple = 0;
    }
    return (int)max(minutesLeft, 0);
}

int pomodoroSecondsLeft() {
    int seconds = (int)(pomodoroEpic - unixtime());

    return (int)max(seconds, 0);
}

int timezone(int time, int offset) {
    // insert earliest time always
    // do not use negative offsets
    return ((time + offset) * 100) % 2400;
}

void clockSetup() {
    // initializing input button
    setupPomodoro();

    // initializing the rtc
    if(!rtc.begin()) {
        Serial.println("Couldn't find RTC!");
        Serial.flush();
    }
    
    if(rtc.lostPower()) {
        // this will adjust to the date and time at compilation
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
    //adjust();
    //we don't need the 32K Pin, so disable it
    rtc.disable32K();
}

void clockSetup(int year, int month, int day, int hour, int minute)
{
    rtc.adjust(DateTime(year, month, day, hour, minute, 00)); // UTC
    clockSetup();
}

void clockTick() {
    // TODO library doesn't decrement `pomodoroMultiple`.
    if (pomodoroButtonPressed())
        pomodoroButtonExecute();

    pomodoroTick(rtc.now().minute());
}