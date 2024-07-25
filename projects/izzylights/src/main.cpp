//
// Created by trevor on 7/5/24.
//
#include "Arduino.h"
#include "pins.h"

struct State {
    int r;
    int g;
    int b;
} state;

void setupPots()
{
}

void tickPots(State *s)
{
    s->r = analogRead(RED_PIN);
    s->g = analogRead(GREEN_PIN);
    s->b = analogRead(BLUE_PIN);
}

void setupLEDDisplay()
{
    // TODO: INPUT

    pinMode(RED_LED, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);
    pinMode(BLUE_LED, OUTPUT);
}

void displayLED(State s)
{
    analogWrite(RED_LED,    s.r < 20 ? 0 : s.r / 4);
    analogWrite(GREEN_LED,  s.g < 20 ? 0 : s.g / 4);
    analogWrite(BLUE_LED,   s.b < 20 ? 0 : s.b / 4);
}

void setup()
{
    Serial.begin(9600);
    setupLEDDisplay();
    setupPots();
    digitalWrite(RED_LED, HIGH);
    delay(500);
    digitalWrite(RED_LED, LOW);
}

void loop()
{
    tickPots(&state);
    displayLED(state);
    Serial.println(state.r);
    delay(1);
}