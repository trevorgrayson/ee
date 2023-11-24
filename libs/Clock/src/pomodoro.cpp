//
// Created by Trevor Grayson on 10/2/23.
//
#include "pomodoro.h"

#include "clock.h"
#include "zelda.h"
#include "Arduino.h"

#define POMODORO_PIN 13
#define ALARM_PIN 14  // A0

int modulusSet = 0;


void soundAlarm() {
    tone(ALARM_PIN, 100);
    delay(500);
    pinMode(ALARM_PIN, INPUT);
}

/*
 * Set "timer" to go off on the modulus of the next
 * timeperiod.
 *
 * TODO
 * first press: mod 30, half hours
 * second: mod 15, every quarter hour
 * third: mod 10, every ten minutes
 * fourth: off
*/
int setMeetingModulus() {
    modulusSet = 30;
    return modulusSet;
    switch (modulusSet) {
        case 0: modulusSet = 30;
        case 30: modulusSet = 15;
        case 15: modulusSet = 10;
    }
    return modulusSet * 1;
}

/*
 * is the button pressed?
 */
bool pomodoroButtonPressed() {
    return !digitalRead(POMODORO_PIN);  // TODO
}


/*
 * Arduino Hooks
 */

/*
 * Arduino setup()
 */
void setupPomodoro() {
    pinMode(POMODORO_PIN, INPUT_PULLUP);
    pinMode(ALARM_PIN, INPUT);
}

void quiet() {
    // clear the humming noise
    noTone(ALARM_PIN);
    pinMode(ALARM_PIN, INPUT);
    modulusSet = 0;
}
/*
 * Arduino loop()
 */
void pomodoroTick(int minutes) {
    // gate clause, if modulus not set
    if (!modulusSet) {
        return;
    }

    // alert on the next half hour
    // TODO Test new modulusSet logic
    if (minutes % modulusSet == 0) {
        // soundAlarm();
        playZelda();
        quiet();
    }
}
