//
// Created by trevor on 4/29/23.
//

#include "Keypad.h"
#include "telekeypad.h"

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
          {'1', '2', '3', '*'}, // Add
          {'4', '5', '6', '/'}, // Sub
          {'7', '8', '9', '+'}, // Multi
          {'.', '0', '#', '-'}  // Divide
};
byte rowPins[ROWS] = { 4, 0, 2, 15};
byte colPins[COLS] = {18, 5, 17, 16};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

char getKey() {
    return customKeypad.getKey();
}