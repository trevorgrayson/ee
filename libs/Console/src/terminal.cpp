//
// Created by trevor on 11/17/2023.
//

#include "Arduino.h"
#include "../include/terminal.h"

#define TIMEOUT 500

String terminalReceive() {
    // listen on Serial for incoming data
    // save the data in a string
    String inputString = "";
    boolean stringComplete = false;

    unsigned long startTime = millis();

    while ((millis() - startTime) < TIMEOUT) {
        if (Serial1.available()) {
            // get the new byte:
            char inChar = Serial1.read();
            // add it to the inputString:
            inputString += inChar;
            // if the incoming character is a newline, set a flag
            // so the main loop can do something about it:
            if (inChar == '\n') {
                stringComplete = true;
            }
            delay(5); // 1 char takes 1 millisecond to transmit
        }
    }
    return inputString;
}
