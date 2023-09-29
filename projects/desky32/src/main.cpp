/*********
  Complete project details at https://randomnerdtutorials.com
  
  This is an example for our Monochrome OLEDs based on SSD1306 drivers. Pick one up today in the adafruit shop! ------> http://www.adafruit.com/category/63_98
  This example is for a 128x32 pixel display using I2C to communicate 3 pins are required to interface (two I2C and one reset).
  Adafruit invests time and resources providing this open source code, please support Adafruit and open-source hardware by purchasing products from Adafruit!
  Written by Limor Fried/Ladyada for Adafruit Industries, with contributions from the open source community. BSD license, check license.txt for more information All text above, and the splash screen below must be included in any redistribution. 
*********/
#include <stdio.h>
#include <Arduino.h>

#include "pins.h"
#include "enums.h"
#include "dogm204.h"
#include "telekeypad.h"
#include "calculator.h"
#include "ThermalPrinter.h"
#include "btcalc.h"
#include "views.h"


int _mode = CALC_MODE;

int mode() {
    return _mode;
}

void setMode(int mode) {
    _mode = mode;
}

void setup() {
    setupDOGM();
    cursor(7, 1);
    print("DeSKY.");

    setupBTCalc();

    pinMode(SEND_PIN, INPUT_PULLUP);
}

void loop() {
    char key = getKey();
    int selectedMode = int(key - 48);
    int shouldSurrender = 0;

    btSendButton(getRegister(1));
    if (mode() == KEYPAD_MODE && shouldSend()) {
        setMode(OPER_MODE);
        view(mode(), key);
        return;
    }
    if(key) {
        switch(mode()) {
            case OPER_MODE:
                if (isNum(key)) {
                    setMode(selectedMode);
                    clear();
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
        clear();
        operatorView();
    }
}
