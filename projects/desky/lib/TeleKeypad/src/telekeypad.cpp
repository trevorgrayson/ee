//
// Created by trevor on 4/29/23.
//

#include "Keypad.h"
#include "telekeypad.h"


const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
//        {'1', '4', '7', '*'},
//        {'2', '5', '8', '0'},
//        {'3', '6', '9', '#'},
//        {'+', '-', '*', '/'}
          {'1', '2', '3', '*'}, // Add
          {'4', '5', '6', '/'}, // Sub
          {'7', '8', '9', '+'}, // Multi
          {'.', '0', '#', '-'}  // Divide
};
// nodemcu pin order: 15, 13, 12, 14, 02, 00, 4, 5
// byte rowPins[ROWS] = {16, 0, 2, 14};
byte rowPins[ROWS] = {14, 12, 13, 10};  // not 15
// byte colPins[COLS] = {12, 13, 15, 3};
byte colPins[COLS] = {0, 2, 9, 3};
// ADDING D8: 15

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

char getKey() {
    return customKeypad.getKey();
}