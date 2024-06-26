/**************************************************************************
 This is an example for our Monochrome OLEDs based on SSD1306 drivers

 Pick one up today in the adafruit shop!
 ------> http://www.adafruit.com/category/63_98

 This example is for a 128x32 pixel display using I2C to communicate
 3 pins are required to interface (two I2C and one reset).

 Adafruit invests time and resources providing this open
 source code, please support Adafruit and open-source
 hardware by purchasing products from Adafruit!

 Written by Limor Fried/Ladyada for Adafruit Industries,
 with contributions from the open source community.
 BSD license, check license.txt for more information
 All text above, and the splash screen below must be
 included in any redistribution.
 **************************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define CARDKB_ADDR 0x5F  //Define the I2C address of CardKB.

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define BACKSPACE 8
#define ENTER 13

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

char buff[50];
int offset = 0;

void refresh() {
    display.clearDisplay();
    display.setCursor(0,0);
    display.print(buff);
    display.setCursor(0,20);
    display.display();
    delay(100);
}

void setup() {
    Serial.begin(9600);
    Wire.begin(4, 5);

    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
        Serial.println(F("SSD1306 allocation failed"));
        for(;;); // Don't proceed, loop forever
    }

    display.setRotation(2);
    display.clearDisplay();

    display.drawPixel(10, 10, SSD1306_WHITE);

    display.display();
    delay(1000);
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    display.setCursor(0,0);
    Serial.println("Start.");
}

void loop() {
    int bytes = Wire.requestFrom(CARDKB_ADDR, 1, false);
    char c = 0;
    while (Wire.available()) {
        c = Wire.read();

        if (c != 0)
        {
            if (offset >= 19) {
                offset = 0;
                //display.clearDisplay();
            }

            buff[offset] = c;
            offset++;
            Serial.print(c);
            refresh();
        }

        switch (c) {
            case BACKSPACE:
                buff[offset] = ' ';
                offset--;
                break;
            case ENTER:
                // TODO Save text
                memset(buff, 0, sizeof buff);
                buff[0] = '\0';
                offset = 0;
                refresh();
                break;
            case 0:
                break;

        }
    }
//    delay(400);
}

void writeToScreen() {
    display.clearDisplay();

    display.setTextSize(1);             // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    display.setCursor(0,0);             // Start at top-left corner
    display.println(F("Hello, world!"));

    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    display.println(3.141592);

    display.setTextSize(2);             // Draw 2X-scale text
    display.setTextColor(SSD1306_WHITE);
    display.print(F("0x")); display.println(0xDEADBEEF, HEX);

    display.display();
}