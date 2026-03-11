//
// Created by trevor on 8/6/2023.
//

#define ZULU 0
#define JFK 1
#define LAX 2
#define IST 5

int rtcLostPower();
void clockSetup();
void clockSetup(int year, int month, int day, int hour, int minute);
void clockTick();

int clockTimeDigits();
int clockTimeDigitsForTZ(int tz);

void adjust();
void adjustHours(int num);
void adjustMinutes(int num);

int date();

int timezone(int time, int offset);

// palmadoro
bool pomodoroButtonPressed();
void pomodoroSetEpic();
int pomodoroTimeLeft();
void pomodoroButtonExecute();

int setMeetingModulus();
void pomodoroTick(int minutes);
void soundAlarm();
