#include <Wire.h>               // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306Wire.h"        // legacy: #include "SSD1306.h"

SSD1306Wire display(0x3c, SDA, SCL, GEOMETRY_128_32);  // ADDRESS, SDA, SCL, OLEDDISPLAY_GEOMETRY  -  Extra param required for 128x32 displays.

int counter = 0;

char buffer[16];
char *format = "hi %04ld";

void drawProgressBarDemo() {
  counter++;
  if (counter == 100) {
    counter = 0;
  }
  int progress = (counter / 5) % 100;
  // draw the progress bar
  display.drawProgressBar(0, 32, 120, 10, progress);

  // draw the percentage as String
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 15, String(progress) + "%");
}

void viewSetup() {
  display.init();
  display.flipScreenVertically();
  display.displayOn();
  display.setFont(ArialMT_Plain_24); // 10 16 24
  display.setTextAlignment(TEXT_ALIGN_LEFT);
}

void print(String s) {
  display.drawString(0, 0, s);
}

void printOn(String s, int line) {
  display.drawString(10*line, 0, s);
}

void hiscore(long score) {
  //display.setTextAlignment(TEXT_ALIGN_RIGHT);
  sprintf(buffer, format, score);
  display.drawString(80, 0, (String)buffer);
  //display.setTextAlignment(TEXT_ALIGN_LEFT);
}

void printFrame(int count) {
  display.drawString(0, 20, String(count));
}

void isPressed() {
  display.drawString(12, 20, "PRESSED");
}

void printWifiStatus(bool online) {
  if(online) {
    display.drawString(118, 16, "x");
  } else {
    display.drawString(118, 16, "o");
  }
}

void viewRender() { display.display(); }
void clear()      { display.clear();   }
