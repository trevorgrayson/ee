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

BleKeyboard bleKeyboard("DeSKY", "tg.", 100);

#define CALC_MODE 1
#define DEBOUNCE_DELAY 50

char cmd[] = "                    ";
int offset = 0;
int ZERO = 0;

// debounced send
int sendState = 0;
int sendStateLast = 0;
int sendStateTime = millis(); // renam


int mode() {
    return CALC_MODE;
}

void setup() {
    Serial.begin(115200);

    setupLCD();
    print("hello.");
    delay(200);
    bleKeyboard.begin();
    bleKeyboard.setBatteryLevel(100);

    setupThermalPrinter();
    delay(2000);
    receiptPrint("");
    receiptPrint("Calc Time");

    pinMode(SEND_PIN, INPUT_PULLUP);
}

void loop() {
    char key = getKey();
    int sendReading = digitalRead(SEND_PIN);

    Serial.println(sendReading);

    if (sendReading == LOW && sendStateLast == HIGH) {
        bleKeyboard.print(getRegister(1));
        delay(500);
        return;
    }

    if (sendReading != sendStateLast) {
        sendStateLast = sendReading;
    }

//    if(sendReading != sendStateLast) {
//        sendStateTime = millis();
//    }
//    if ((millis() - sendStateTime) > DEBOUNCE_DELAY) {
//        if (sendReading != sendState) {
//            sendState = sendReading;
//
//            if (sendState == HIGH) {
//                bleKeyboard.print(getRegister(1));
//                return;
//            }
//        }
//    }

//    if((getRegister(0) == 0 && (key && ZERO == double(key)))) {  // pressing zero when reg0 is zero will send
//        bleKeyboard.print(getRegister(1));
//        return;
//    }

    if(key) {
        switch(CALC_MODE) {
            case CALC_MODE:
                calcPress(key);

                // view
                cursor(0, 0);
                sprintf(cmd, "                    ");
                sprintf(cmd, "%f", getRegister(0));
                print(cmd);
                cursor(0, 1);
                sprintf(cmd, "                    ");
                sprintf(cmd, "%f", getRegister(1));
                print(cmd);
        }
    }
}
