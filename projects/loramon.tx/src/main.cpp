/*https://github.com/sandeepmistry/arduino-LoRa/tree/master/examples
 *
 *
 */
#include <SPI.h>
#include <LoRa.h>

#define ss 18
#define rst 14
#define dio0 26

int counter = 0;

void setup() {
    Serial.begin(115200);
    while (!Serial);

    Serial.println("LoRa Sender");
    LoRa.setPins(ss, rst, dio0);

    if (!LoRa.begin(915E6)) {
        Serial.println("Starting LoRa failed!");
        while (1);
    }
}

void loop() {
    Serial.print("Sending packet: ");
    Serial.println(counter);

    // send packet
    LoRa.beginPacket();
    LoRa.print("hello ");
    LoRa.print(counter);
    LoRa.endPacket();

    counter++;

    delay(5000);
}

/*
#include <Wire.h>
#include "SSD1306.h"
#include <SPI.h>
#include <LoRa.h>

#define SDA    4
#define SCL   15
#define RST   16

SSD1306  display(0x3c, SDA, SCL, RST);

char buffer[50] = "starting.";

void setup() {
    Serial.begin(9600);
    while (!Serial);

    display.init();
    //display.flipScreenVertically();

    Serial.println("Starting");
    if (!LoRa.begin(915E6)) {
        Serial.println("Starting LoRa failed!");
//        while (1);
    }
    // delay(1000);
    display.clear();
    display.drawString(0, 0, "Listening to LoRa");
    Serial.println("listening");
    display.display();
}

void loop() {
    display.clear();
    display.drawString(0, 0, buffer);
    display.display();

    return;

    int packetSize = LoRa.parsePacket();
    if (packetSize) {
        // received a packet
        Serial.print("Received packet '");

        int offset = 0;
        // read packet
        while (LoRa.available()) {
            char c = LoRa.read();
            buffer[offset] = c;
            offset++;
            // Serial.print((char) LoRa.read());
        }

        // print RSSI of packet
        Serial.print("' with RSSI ");
        Serial.println(LoRa.packetRssi());
    }

}
*/