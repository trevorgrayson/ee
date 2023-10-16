//
// Created by trevor on 11/4/2022.
//

#include "../include/serial.h"

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27, 20, 4);

#define WIDTH 17

int incomingByte = 0;
int lastByte = 0;

char clear[WIDTH] = "                ";
char lcdDisplay[16];

int offset = 0;
int offsetY = 0;


void print() {
    lcd.setCursor(0, offsetY);
    lcd.print(clear);
    lcd.setCursor(0, offsetY);
    lcd.print(lcdDisplay);
}


void setupSerial() {
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, offsetY);
    print();
}

void scanInput() {
    if (Serial.available() > 0) {
        // read the incoming byte:
        lastByte = incomingByte;
        incomingByte = Serial.read();
        if (incomingByte == '\0') {
            offset = 0;
        }

        if (incomingByte == '\0' && lastByte == '\0') {
            offsetY = (offsetY + 1) % 2;
            print();
        }
        if(incomingByte != '\0') {
            lcdDisplay[offset] = incomingByte;
            lcdDisplay[offset+1] = 0;
            offset++;
            print();
        }

        if(offset >= WIDTH - 1) {
            offset = 0;
            strcpy(lcdDisplay, clear);
        }
    }
}