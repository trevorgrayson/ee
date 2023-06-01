//
// Created by trevor on 5/26/23.
//

void setupFuelRod();
void tickFuelRod();

int rodCurrent();
int rodDepth();
int nextRod();

int actuatorStatus();

int rodLift(int dist);
int rodButtonDepressed();
int power();

void fuelRodScreen(int rodCurrent, int actuatorStatus, int rodDepth);