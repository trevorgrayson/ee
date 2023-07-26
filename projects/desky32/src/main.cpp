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
#include "dsky.h"
#include "ThermalPrinter.h"


#define CALC_MODE 0
#define DSKY_MODE 1
#define OPERATE 0

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

int MODE = CALC_MODE;


/*
 * Router Check mode switch
 */
void surrender(char key) {
    switch(MODE) {
        case CALC_MODE:
            if (calcShouldSurrender(key)) {
                MODE = !MODE;
            }
            break;
        case DSKY_MODE:
            if (dskyShouldSurrender(key))
                MODE = !MODE;
            break;
    }
}

// BT
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

//TODO doubles only. can overload?
void output(int line, double value) {
    char buff[] = "                    ";
    cursor(0, line);
    sprintf(buff, "                    ");
    sprintf(buff, "%f", value);
    print(buff);
}

void setup() {
    Serial.begin(9600);
//    while (Serial.available()) {
//        Serial.read();
//    }

//    setupThermalPrinter();
//    receiptPrint("hello world");
//    footer();

    setupLCD();
    print("hello.");
    bleKeyboard.begin();
    bleKeyboard.setBatteryLevel(100);

    pinMode(SEND_PIN, INPUT_PULLUP);
}


void loop() {
    char key = getKey();

    btSendButton();
    if(key) {
        switch(CALC_MODE) {
            case CALC_MODE:
                calcPress(key);

                // view
                // TODO test if these work.
                output(TOP_LINE, getRegister(1));
                output(BTM_LINE, getRegister(0));

                cursor(0, TOP_LINE);
                sprintf(cmd, "                    ");
                sprintf(cmd, "%f", getRegister(1));
                print(cmd);
                cursor(0, BTM_LINE);
                sprintf(cmd, "                    ");
                sprintf(cmd, "%f", getRegister(0));
                print(cmd);
            case DSKY_MODE:
                dskyPress(key);

                output(TOP_LINE, dskyDisplayLine(TOP_LINE));
        }
    }
}
