//
// Created by trevor on 5/26/24.
//
/* beginning char defines command.
 * following chars are read as input.
 * l -
 * 0-4 - print to console line
 * else print to line 0
 */

#include "../include/listen.h"

#include <Arduino.h>
#include "console.h"
#include "terminal.h"
#include "listen.h"

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
