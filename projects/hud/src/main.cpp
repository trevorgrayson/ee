/*********
  Complete project details at https://randomnerdtutorials.com
  
  This is an example for our Monochrome OLEDs based on SSD1306 drivers. Pick one up today in the adafruit shop! ------> http://www.adafruit.com/category/63_98
  This example is for a 128x32 pixel display using I2C to communicate 3 pins are required to interface (two I2C and one reset).
  Adafruit invests time and resources providing this open source code, please support Adafruit and open-source hardware by purchasing products from Adafruit!
  Written by Limor Fried/Ladyada for Adafruit Industries, with contributions from the open source community. BSD license, check license.txt for more information All text above, and the splash screen below must be included in any redistribution. 
*********/

#include <Arduino.h>
#include "display.h"

void setup() {
    Serial.begin(115200);

    displaySetup();
    orientation();

    testdrawline();      // Draw many lines

    testdrawrect();      // Draw rectangles (outlines)

    testfillrect();      // Draw rectangles (filled)

    testdrawcircle();    // Draw circles (outlines)

    testfillcircle();    // Draw circles (filled)

    testdrawroundrect(); // Draw rounded rectangles (outlines)

    testfillroundrect(); // Draw rounded rectangles (filled)

    testdrawtriangle();  // Draw triangles (outlines)

    testfilltriangle();  // Draw triangles (filled)

    testdrawchar();      // Draw characters of the default font

    testdrawstyles();    // Draw 'stylized' characters

    testscrolltext();    // Draw scrolling text

    testdrawbitmap();    // Draw a small bitmap image

    // Invert and restore display, pausing in-between
    //
//    delay(1000);
//    display.invertDisplay(false);
//    delay(1000);

    //testanimate(logo_bmp, LOGO_WIDTH, LOGO_HEIGHT); // Animate bitmaps
}

void loop() {
}
