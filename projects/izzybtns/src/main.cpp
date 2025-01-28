//
// Created by trevor on 1/26/25.
// https://www.arduino.cc/reference/cs/language/functions/external-interrupts/attachinterrupt/
// https://docs.arduino.cc/language-reference/en/functions/interrupts/noInterrupts/
// atmega interrupt pins https://www.arxterra.com/11-atmega328p-external-interrupts/
//
#include <Arduino.h>
#include "pins.h"


void red() {
    digitalWrite(LEDR, HIGH);
    delay(1000);
    digitalWrite(LEDR, LOW);
}
void green() {
    digitalWrite(LEDG, HIGH);
    delay(1000);
    digitalWrite(LEDG, LOW);
}
void yellow() {
    digitalWrite(LEDY, HIGH);
    delay(1000);
    digitalWrite(LEDY, LOW);
}
void blue() {
    digitalWrite(LEDB, HIGH);
    delay(1000);
    digitalWrite(LEDB, LOW);
}

void promptUsers() {
    digitalWrite(LEDR, HIGH);
    digitalWrite(LEDG, HIGH);
    digitalWrite(LEDB, HIGH);
    digitalWrite(LEDY, HIGH);
    delay(1000);
    digitalWrite(LEDR, LOW);
    digitalWrite(LEDG, LOW);
    digitalWrite(LEDB, LOW);
    digitalWrite(LEDY, LOW);
}

void pinSetup()
{
    pinMode(BTNR, INPUT_PULLUP);
    pinMode(BTNG, INPUT_PULLUP);
    pinMode(BTNB, INPUT_PULLUP);
    pinMode(BTNY, INPUT_PULLUP);

    pinMode(LEDR, OUTPUT);
    pinMode(LEDG, OUTPUT);
    pinMode(LEDB, OUTPUT);
    pinMode(LEDY, OUTPUT);

    // Consider INT0; INT1; pins
    attachInterrupt(digitalPinToInterrupt(BTNR), red, FALLING);  // RISING
    attachInterrupt(digitalPinToInterrupt(BTNR), green, FALLING);  // RISING
    attachInterrupt(digitalPinToInterrupt(BTNR), blue, FALLING);  // RISING
    attachInterrupt(digitalPinToInterrupt(BTNR), yellow, FALLING);  // RISING
}

void setup()
{
    pinSetup();

    noInterrupts();
    interrupts();
}

void loop()
{
    promptUsers();
    interrupts();
}
