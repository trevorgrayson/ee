//
// Created by trevor on 5/26/24.
//

#include "listen.h"

#include <Arduino.h>
#include "terminal.h"
#include "console.h"

char buffer[20];


void listen()
{
    String line = terminalReceive();
    if (line) {
        line.toCharArray(buffer, 20);

        switch (line.charAt(0)) {
            case 'l':
            case 'L':
                toggleConsoleLight();
                break;
            case '!':
                // increment elecromag counter
                break;
            case '0':
                // +1 to remove first "instruction" character
                consolePrintLn(buffer+1, 0);
                break;
            case '1':
                consolePrintLn(buffer+1, 1);
                break;
            case '2':
                consolePrintLn(buffer+1, 2);
                break;
            case '3':
                consolePrintLn(buffer+1, 3);
                break;
            default:
                consolePrintLn(buffer);
        }
    }

}
