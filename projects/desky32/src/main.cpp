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
#include "lcd.h"
#include "telekeypad.h"
#include "calculator.h"

#include <BleKeyboard.h>

BleKeyboard bleKeyboard;

#define CALC_MODE 1

char cmd[] = "                    ";
int offset = 0;


int mode() {
    return CALC_MODE;
}

void setup() {
    Serial.begin(115200);
    setupLCD();
    print("hello.");
    delay(200);
    bleKeyboard.begin();

    pinMode(SEND_PIN, INPUT);
}

void loop() {
    if(digitalRead(SEND_PIN)) {
        bleKeyboard.print(getRegister(1));
        return;
    }

    char key = getKey();
    if(key) {
        switch(CALC_MODE) {
            case CALC_MODE:
                calcPress(key);

                // view
                cursor(0, 0);
                sprintf(cmd, "%f", getRegister(0));
                print(cmd);
                cursor(0, 1);
                sprintf(cmd, "%f", getRegister(1));
                print(cmd);
        }
    }
}
