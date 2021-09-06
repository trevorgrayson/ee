#include "ssd1306.h"
#include "nano_gfx.h"

#include "ESP.h"

void viewSetup() {
  ssd1306_128x64_i2c_init();

  ssd1306_clearScreen();
  ssd1306_setFixedFont(ssd1306xled_font8x16);
  //ssd1306_setFixedFont(ssd1306xled_font6x8);
  ssd1306_clearScreen();
  ssd1306_positiveMode();
  delay(3000);
}

void clear() { ssd1306_clearScreen(); }
  
void print(char *str, int line) {
  ssd1306_printFixed(0,  20*line, str, STYLE_NORMAL);
}
