/*https://github.com/sandeepmistry/arduino-LoRa/tree/master/examples
 *
 *
 */
#include <Wire.h>
#include "SSD1306.h"
#include <SPI.h>
#include <LoRa.h>

#define SDA    4
#define SCL   15
#define RST   16


SSD1306  display(0x3c, SDA, SCL, RST);

void setup() {
    // Serial.begin(9600);
    // while (!Serial);
    display.init();
    //display.flipScreenVertically();

    if (!LoRa.begin(915E6)) {
        Serial.println("Starting LoRa failed!");
        while (1);
    }
}

void loop() {
    int packetSize = LoRa.parsePacket();
    if (packetSize) {
        // received a packet
        Serial.print("Received packet '");

        // read packet
        while (LoRa.available()) {
            Serial.print((char) LoRa.read());
        }

        // print RSSI of packet
        Serial.print("' with RSSI ");
        Serial.println(LoRa.packetRssi());
    }
    display.clear();
    display.drawString(0, 0, "sup?");
    display.display();
}
//#include <SPI.h>
//#include <LoRa.h>
//
//void setup() {
//    Serial.begin(9600);
//    while (!Serial);
//
//    Serial.println("LoRa Receiver");
//
//    if (!LoRa.begin(915E6)) {
//        Serial.println("Starting LoRa failed!");
//        while (1);
//    }
//}
//
//void loop() {
//    // try to parse packet
//    int packetSize = LoRa.parsePacket();
//    if (packetSize) {
//        // received a packet
//        Serial.print("Received packet '");
//
//        // read packet
//        while (LoRa.available()) {
//            Serial.print((char)LoRa.read());
//        }
//
//        // print RSSI of packet
//        Serial.print("' with RSSI ");
//        Serial.println(LoRa.packetRssi());
//    }
//}
/*
#include <SPI.h>
#include <LoRa.h>

int counter = 0;

void setup() {
    Serial.begin(9600);
    while (!Serial);

    Serial.println("LoRa Sender");

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
*/
