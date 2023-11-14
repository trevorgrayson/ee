//
// Created by trevor on 8/6/2023.
//

void clockSetup();

void clockTick();

int clockTimeDigits();

void adjust();

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