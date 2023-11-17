//
// Created by trevor on 11/17/2023.
//

#include "Arduino.h"
#include "terminal.h"

String terminalReceive() {
    // listen on Serial for incoming data
    // save the data in a string
    String inputString = "";
    boolean stringComplete = false;


        while(Serial.available()) {
            // get the new byte:
            char inChar = Serial.read();
            // add it to the inputString:
            inputString += inChar;
            // if the incoming character is a newline, set a flag
            // so the main loop can do something about it:
            if (inChar == '\n') {
                stringComplete = true;
            }
            delay(50);
        }

    return inputString;
}
