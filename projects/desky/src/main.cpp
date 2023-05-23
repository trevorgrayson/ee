/*********
  Complete project details at https://randomnerdtutorials.com
  
  This is an example for our Monochrome OLEDs based on SSD1306 drivers. Pick one up today in the adafruit shop! ------> http://www.adafruit.com/category/63_98
  This example is for a 128x32 pixel display using I2C to communicate 3 pins are required to interface (two I2C and one reset).
  Adafruit invests time and resources providing this open source code, please support Adafruit and open-source hardware by purchasing products from Adafruit!
  Written by Limor Fried/Ladyada for Adafruit Industries, with contributions from the open source community. BSD license, check license.txt for more information All text above, and the splash screen below must be included in any redistribution. 
*********/

#include <Arduino.h>
// #include "lcd.h"
#include "telekeypad.h"
#include "state.h"
#include "client.h"
#include "calculator.h"
#include "lcd.h"

#define CALC_MODE 1

char cmd[] = "                    ";
int offset = 0;

struct State state;

int mode() {
    return CALC_MODE;
}

void setup() {
    Serial.begin(115200);
    setupLCD();
    print("hello.");
    delay(200);
}

void loop() {
    char key = getKey();
    if(key) {
        cmd[offset] = key;
        offset++;

        // calc mode
        calcPress(key);
        // print(calcDisplay(key));
        cursor(0, 0);
        print(cmd);
    }
}
