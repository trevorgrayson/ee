/*https://github.com/sandeepmistry/arduino-LoRa/tree/master/examples
 *
 *
 */
#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "presence.h"
#include "presenceState.h"


#define ss 18
#define rst 14
#define dio0 26

#define OLED_RST 16
#define OLED_SDA 4
#define OLED_SCL 15

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST);

int counter = 0;

struct Presence state;
char buffer[20];

void setup() {
    Wire.begin(OLED_SDA, OLED_SCL);
    Serial.begin(115200);
    while (!Serial);

    Serial.println("LoRa Tx");
    LoRa.setPins(ss, rst, dio0);

    if (!LoRa.begin(915E6)) {
        Serial.println("Starting LoRa failed!");
        while (1);
    }

    // setupPresence();

    if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("SSD1306 allocation failed"));
        for(;;); // Don't proceed, loop forever
    }

    display.clearDisplay();
    display.setTextSize(3);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.print("tx mode");
    display.display();
    delay(2000);
}

void loop() {
//    Serial.print("Sending packet: ");
//    Serial.println(counter);
//    presenceState();
    sprintf(buffer, "%d,%d",
            motionLevel(),
            noiseLevel()
            );
    Serial.println(buffer);

    display.clearDisplay();
    display.setCursor(0,0);
    display.println("tx");
    display.println(F(buffer));
    display.display();

    // only send if values changed
    // send packet
    LoRa.beginPacket();
    LoRa.print(buffer);
    LoRa.print(counter);
    LoRa.endPacket();

    counter++;

    delay(2000);
}
