#include "calculator.h"

float reg0 = 0;
float reg1 = 0;
char operatr = 0;
int decimal = 10;

float getRegister(int regNum) {
    if (regNum) {
        return reg1;
    }
    return reg0;
}

int isNum(char key) {
    if(key < 58 && key > 47) {
        return 1;
    }
    return 0;
}

int isOperator(char key) {
    if(key < 48 && key > 41) {
        return 1;
    }
    return 0;
}

float operate() {
    switch(operatr) {
        case '*': return reg1 * reg0;
        case '/': return reg1 / reg0;
        case '+': return reg1 + reg0;
        case '-': return reg1 - reg0;
    }
    return reg1;
}

void calcPress(char key) {
    if(isNum(key)) {
        if(decimal == 10) {
            reg0 = reg0 * 10 + (key - 48);
        } else {
            reg0 = reg0 * decimal + (key - 48);
            decimal = decimal / 10;
        }

    } else if(isOperator(key)) {
        operatr = key;
        if(reg0 == 0) {
            return;
        }

        if(reg1 == 0) {
            reg1 = reg0;
        } else {
            reg1 = operate();
        }
        reg0 = 0;
    } else if(key == '#') { // CLEAR
        reg0 = 0;
        decimal = 10;
    } else if(key == '.' && decimal > 0) {
        // janky, but expecting to set decimal to be 0.1 and
        // make it a magnitude smaller every button press.
        decimal = 0.1;
    }
}

float calcDisplay(char key) {
    if(isNum(key)) {
        return reg0;
    } else if(isOperator(key)) {
        return reg1;
    } else if(key == '#') { // ENTER
        //Serial.println(reg0, reg1);
    }
    return 0;
}
