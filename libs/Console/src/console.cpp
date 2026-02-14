//
// Created by trevor on 11/14/2023.
//

#include "../include/console.h"

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);
//0x27 (39) default I2C Address
// 20 cols
//  4 rows

int consoleLight = 1;

void setupConsole() {
    lcd.init();                      // initialize the lcd

    // lcd.backlight();
    lcd.noBacklight();
}

void consolePrintLn(char c[], int y) {
    lcd.setCursor(0, y);
    lcd.print(c);
}

void consolePrintLn(char c[]) {
    consolePrintLn(c, 0);
}

void consolePrint() {
    lcd.setCursor(0,0);
    lcd.print("CSIF 40k DSIF 80k");
    lcd.setCursor(0,1);
    lcd.print("MRKT");
    lcd.setCursor(0,2);
    lcd.print("Evolve Taba Gal TA");  //Things that are expected and landed
    lcd.setCursor(0,3);
    lcd.print("DBT: 8hr Egress:9999"); // last build, scheduled egress that are expected and landed
}

void consoleLightOn() {
    lcd.backlight();
}

void consoleLightOff() {
    lcd.noBacklight();
}

void toggleConsoleLight() {
    consoleLight = !consoleLight;
    if (consoleLight)
        lcd.backlight();
    else
        lcd.noBacklight();
}