//
// Created by trevor on 5/14/23.
//

#include "lcd.h"
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void backlight() {
    lcd.backlight();
}

void cursor(int x, int y) {
    lcd.setCursor(x, y);
}

void print(char s[]) {
    lcd.print(s);
}

void setupLCD()
{
    lcd.init();                      // initialize the lcd
    // Print a message to the LCD.
    backlight();
    cursor(0, 0);
}
