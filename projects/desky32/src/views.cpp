//
// Created by Trevor Grayson on 9/10/23.
//
#include <stdio.h>
#include "views.h"
#include "pins.h"
#include "enums.h"
#include "dogm204.h"
#include "calculator.h"

// display
#define TOP_LINE 0
#define BTM_LINE 1


char cmd[] = "                    ";


void operatorView() {
    cursor(0, TOP_LINE);
    sprintf(cmd, "1. Calculator    ");
    print(cmd);
    cursor(0, 1);
    sprintf(cmd, "2. Keypad           ");
    print(cmd);
    cursor(0, 2);
    sprintf(cmd, "C. STOre           ");
    print(cmd);
    cursor(0, 3);
    sprintf(cmd, "D. ReCaLL           ");
    print(cmd);
}

void calcView() {
    cursor(0, TOP_LINE);
    sprintf(cmd, "                    ");
    sprintf(cmd, "%f          ", getRegister(1));
    print(cmd);
    cursor(0, BTM_LINE);
    sprintf(cmd, "                    ");
    sprintf(cmd, "%f          ", getRegister(0));
    print(cmd);
}

void keypadView(char key) {
    cursor(0, TOP_LINE);
    sprintf(cmd, "Keypad %c        ", key);
    print(cmd);
}

void debug(char key) {
    sprintf(cmd, "DEBUG %c        ", key);
    cursor(15, BTM_LINE);
    print(cmd);
}
void view(int mode, char key) {
    switch(mode) {
        case OPER_MODE:
            operatorView();
            break;
        case CALC_MODE:
            calcView();
            break;
        case KEYPAD_MODE:
            keypadView(key);
    }
}
