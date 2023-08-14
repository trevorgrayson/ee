/*********
  Complete project details at https://randomnerdtutorials.com
  
  This is an example for our Monochrome OLEDs based on SSD1306 drivers. Pick one up today in the adafruit shop! ------> http://www.adafruit.com/category/63_98
  This example is for a 128x32 pixel display using I2C to communicate 3 pins are required to interface (two I2C and one reset).
  Adafruit invests time and resources providing this open source code, please support Adafruit and open-source hardware by purchasing products from Adafruit!
  Written by Limor Fried/Ladyada for Adafruit Industries, with contributions from the open source community. BSD license, check license.txt for more information All text above, and the splash screen below must be included in any redistribution. 
*********/
#include <stdio.h>
#include <Arduino.h>
#include <BleKeyboard.h>

#include "pins.h"
#include "lcd.h"
#include "telekeypad.h"
#include "calculator.h"
#include "ThermalPrinter.h"

#define OPER_MODE 0
#define CALC_MODE 1
#define KEYPAD_MODE 2
#define DESKY 3

#define DEBOUNCE_DELAY 50

// display
#define TOP_LINE 0
#define BTM_LINE 1

BleKeyboard bleKeyboard("DeSKY", "tg.", 100);

char cmd[] = "                    ";
int offset = 0;
int ZERO = 0;

// debounced send
int sendState = 0;
int sendStateLast = 0;
int sendStateTime = millis(); // rename

int _mode = CALC_MODE;

int mode() {
    return _mode;
}

void setMode(int mode) {
    _mode = mode;
}

void setup() {
    setupLCD();
    print("hello.");
    bleKeyboard.begin();
    bleKeyboard.setBatteryLevel(100);

    pinMode(SEND_PIN, INPUT_PULLUP);
}

void btSend(char key) {
    bleKeyboard.print(key);
}

void btSendButton() {
    int sendReading = digitalRead(SEND_PIN);

    if (sendReading == LOW && sendStateLast == HIGH) {
        bleKeyboard.print(getRegister(1));
        delay(500);
        return;
    }

    if (sendReading != sendStateLast) {
        sendStateLast = sendReading;
    }
}

void operatorView() {
    cursor(0, TOP_LINE);
    sprintf(cmd, "1. Calc 2.Keypad   ");
    print(cmd);
    cursor(0, BTM_LINE);
    sprintf(cmd, "2. Keypad           ");
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

void blankView() {
    cursor(0, TOP_LINE);
    sprintf(cmd, "                    ");
    print(cmd);
    cursor(0, BTM_LINE);
    sprintf(cmd, "                    ");
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

void loop() {
    char key = getKey();
    int selectedMode = int(key - 48);
    int shouldSurrender = 0;

    btSendButton();
    if(key) {
        switch(mode()) {
            case OPER_MODE:

                if (isNum(key)) {
                    setMode(selectedMode);
                }
                break;

            case CALC_MODE:
                shouldSurrender = calcPress(key);
                break;

            case KEYPAD_MODE:
                btSend(key);
                break;
        }
        view(mode(), key);
    }
    if (shouldSurrender == 1) {
        shouldSurrender = 0;
        setMode(OPER_MODE);
        operatorView();
    }
}
