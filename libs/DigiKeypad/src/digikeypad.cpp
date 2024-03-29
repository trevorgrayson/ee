//
// Created by trevor on 4/29/23.
//

#include "Keypad.h"
#include "digikeypad.h"


const byte ROWS = 4;
const byte COLS = 3;

char hexaKeys[ROWS][COLS] = {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'},
        {'*', '0', '#'}
        //  {'1', '2', '3', '+'}, // Add
        //  {'4', '5', '6', '-'}, // Sub
        //  {'7', '8', '9', '*'}, // Multi
        //  {'*', '0', '#', '/'}  // Divide
};

byte rowPins[ROWS] = {14,12,13,9};
byte colPins[COLS] = {10,0,2};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

char getKey() {
    return customKeypad.getKey();
}