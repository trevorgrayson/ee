//
// Created by trevor on 7/30/25.
//
#include <Arduino.h>
#include "vault.h"


void setup()
{
    Serial.begin(9600);
}

bool shouldRecall()
{
    return false;
}

void loop()
{
    if (!Serial.available()) return;
    String line = Serial.readStringUntil('\n');

    if(shouldRecall())
    {

    }
    Serial.print("RCVD: ");
    Serial.println(line);
    secrets[offset] = line;
    offset++;
    if (offset > 99) { offset = 0; }



}

