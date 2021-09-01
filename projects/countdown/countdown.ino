/*
 * Countdown to TBD baby.
 */
#include <Arduino.h>
#include <TM1637TinyDisplay.h>

#define FLASH_BTN 0
#define CLK 5
#define DIO 4
#define BUTTON 15

TM1637TinyDisplay display(CLK, DIO);

int mills = 0;
int seconds = 0;
int minutes = 0;
int hours = 0;
int oneDay = 24*60*60;

int btn() { return digitalRead(BUTTON); }

void tick() {
  if(btn()) {
    setup();
  }
  mills++;
  if(mills > 20){
    mills = 0;
    seconds++;
  }
  if(seconds >= 59) {
    seconds = 0;
    minutes++;
  }
  if(minutes >= 59) {
    minutes = 0;
    hours++;
  }
}

void reset() {
    mills = 0;
    seconds = 0;
    minutes = 0;
    hours = 0;
}

void setup() {
  pinMode(FLASH_BTN, INPUT);
  pinMode(BUTTON, INPUT);
  display.setBrightness(0x02);
  display.showString("ISAAC");
  reset();
  delay(500);
  display.clear();
}

void loop() {
  display.showNumber(hours*100 + minutes);
  delay(50);
  tick();
}

