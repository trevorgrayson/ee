/*
 * Countdown to TBD baby.
 */
#include <Arduino.h>
#include <TM1637TinyDisplay.h>

#define FLASH_BTN 0
#define CLK 5
#define DIO 4

TM1637TinyDisplay display(CLK, DIO);

int daysLeft = 25;
int seconds = 0;
int oneDay = 24*60*60;

void setup() {
  pinMode(FLASH_BTN, INPUT);
  display.setBrightness(0x03);
  display.showString("HELLO");
  delay(500);
  display.clear();
}

void loop() {
  if(!digitalRead(FLASH_BTN)) {
    daysLeft--;
    seconds = 0;
  }

  display.showNumber(daysLeft);
  delay(1000);

  seconds++;
  if(seconds >= oneDay) {
    seconds = 0;
    daysLeft--;
  }
}

