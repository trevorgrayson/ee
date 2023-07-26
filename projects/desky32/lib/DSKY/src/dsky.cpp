//
// Created by trevor on 7/26/2023.
//

#include "dsky.h"

double dskyReg0 = 0;


int dskyShouldSurrender(char key) {
    return key == 0;
}

void dskyPress(char key) {
    dskyReg0 = dskyReg0 * 10 + (key - 48);
}

double dskyDisplayLine(int line) {
    return dskyReg0;
}