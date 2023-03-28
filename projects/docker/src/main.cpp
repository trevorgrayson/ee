// https://github.com/gamegine/HCSR04-ultrasonic-sensor-lib
#include <HCSR04.h>

#include "lights.h"
#include "display.h"

#define TRIGGER 4
#define ECHO 5
#define DELAY 60
#define MARGIN_OF_TARGET 5
#define MARGIN 20
#define APPROACHING 426

#define FOOT_PER_CM 30.48

HCSR04 hc(TRIGGER, ECHO);

struct State {
    int distance = 0;
    int target = 0;
    int lights = 0;
} state;

int classify(State state)
{
    int lights = 0;
    if (
        state.distance <= state.target + MARGIN_OF_TARGET &&  // On Target
        state.distance >= state.target - MARGIN_OF_TARGET)
    {
        lights = 0b001;
    } else
    if (
        state.distance <= state.target + MARGIN &&
        state.distance >= state.target - MARGIN)
    {
        lights = 0b010;
    } else
    if (state.distance < APPROACHING)
    {
        lights = 0b100;
    } else
    {
        return 0b111;
    }

    return lights;
}

bool shouldCalibrate(int dist)
{
    return dist < 100;
}

void setup()
{
    Serial.begin(9600);
    initDisplay();

    state.distance = hc.dist();

    if(shouldCalibrate(state.distance))
        state.target = state.distance;
}

void loop()
{
    state.distance = hc.dist();
    state.lights = classify(state);

    Serial.println( hc.dist() ); // return current distance (cm) in serial
    setDisplay(state.distance);
    setLights(state.lights);

    delay(DELAY);
}
