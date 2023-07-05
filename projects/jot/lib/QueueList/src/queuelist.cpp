//
// Created by Trevor Grayson on 7/4/23.
//

#include "queuelist.h"

#include <cstring>
// #include <iostream>

#define MSG_LEN 20

#define BACKSPACE 8
#define ENTER 13

static char buff[MSG_LEN];
static int offset = 0;

char* buffer() {
    return buff;
}

void processChar(char c) {
    if (c != 0)
    {
        if (offset >= 19) {
            offset = 0;
            //display.clearDisplay();
        }

        buff[offset] = c;
        offset++;
        // Serial.print(c);
    }

    switch (c) {
        case BACKSPACE:
            buff[offset] = ' ';
            offset--;
            break;
        case ENTER:
            // TODO Save text
            //strcpy(buff, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0")
            memset(buff, 0, sizeof buff);
            break;
        case 0:
            break;

    }
}