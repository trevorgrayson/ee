//
// Created by trevor on 11/14/2023.
//

#include "console.h"

#include <LiquidCrystal_I2c.h>

LiquidCrystal_I2C lcd(0x27,20,4);



void setupConsole() {
    lcd.init();                      // initialize the lcd
    // Print a message to the LCD.
    lcd.backlight();
    lcd.setCursor(0,0);
    lcd.print("CSIF 40k DSIF 80k");
    lcd.setCursor(0,1);
    lcd.print("MRKT");
    lcd.setCursor(0,2);
    lcd.print("Evolve Taba Gal TA");  //Things that are expected and landed
    lcd.setCursor(0,3);
    lcd.print("DBT: 8hr Egress:9999"); // last build, scheduled egress that are expected and landed
}

void tickConsole() {

}