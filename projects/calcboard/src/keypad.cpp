//
// Created by trevor on 3/27/23.
//
#include "keypad.h"

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
        {'1', '4', '7', '*'},
        {'2', '5', '8', '0'},
        {'3', '6', '9', '#'},
        {'+', '-', '*', '/'}
        //  {'1', '2', '3', '+'}, // Add
        //  {'4', '5', '6', '-'}, // Sub
        //  {'7', '8', '9', '*'}, // Multi
        //  {'*', '0', '#', '/'}  // Divide
};
// nodemcu pin order: 15, 13, 12, 14, 02, 00, 4, 5
// 5, 4, 3, 2
byte rowPins[ROWS] = {2, 0, 9, 10};
// 8, 7, 6
byte colPins[COLS] = {15, 13, 12, 14};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

char getKey() {
    return customKeypad.getKey();
}