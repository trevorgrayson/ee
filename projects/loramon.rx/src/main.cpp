/*https://github.com/sandeepmistry/arduino-LoRa/tree/master/examples
 *
 *
 */
// http://community.heltec.cn/t/lorawan-preamble-length-undeclared/11484/6
#define LORAWAN_PREAMBLE_LENGTH 8

#include <Wire.h>
#include <SPI.h>
#include <LoRa.h>


void setup() {
    Serial.begin(9600);
    while (!Serial);

    Serial.println("LoRa Receiver");

    if (!LoRa.begin(915E6)) {
        Serial.println("Starting LoRa failed!");
        while (1);
    }
}

void loop() {
    // try to parse packet
    int packetSize = LoRa.parsePacket();
    if (packetSize) {
        // received a packet
        Serial.print("Received packet '");

        // read packet
        while (LoRa.available()) {
            Serial.print((char)LoRa.read());
        }

        // print RSSI of packet
        Serial.print("' with RSSI ");
        Serial.println(LoRa.packetRssi());
    }
}
