//
// Created by Trevor Grayson on 10/2/23.
//
#include "clock.h"
#include "zelda.h"
#include "Arduino.h"

#define ALARM_PIN 14

int modulusSet = 0;

void soundAlarm() {
    tone(ALARM_PIN, 100);
    delay(200);
    noTone(ALARM_PIN);

//    tone(ALARM_PIN, 100);
//    delay(200);
//    tone(ALARM_PIN, 0);
//    delay(200);
//
//    tone(ALARM_PIN, 100);
//    delay(200);
//    tone(ALARM_PIN, 0);
//    delay(200);
}

/*
 * TODO
 * first press: mod 30,
 * second: mod 15
 * third: mod 10
 * fourth: off
*/
void setMeetingModulus() {
    modulusSet = 1;
}

void pomodoroTick(int minutes) {
    if (!modulusSet) {
        return;
    }

    if (minutes % 30 == 0) {
//        soundAlarm();
        playZelda();
        noTone(ALARM_PIN);
        modulusSet = 0;
    }
}