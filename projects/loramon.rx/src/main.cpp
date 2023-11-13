/*********
  Modified from the examples of the Arduino LoRa library
  More resources: https://randomnerdtutorials.com
*********/

#include <SPI.h>
#include <LoRa.h>

//define the pins used by the transceiver module
#define ss 8
#define rst 12
#define dio0 14  // 2

//static const uint8_t SDA_OLED = 17;
//static const uint8_t SCL_OLED = 18;
//static const uint8_t RST_OLED = 21;
//
//static const int8_t SW_LoRa = -1;
//static const uint8_t SS_LoRa = 8;
//static const uint8_t SCK_LoRa = 9;
//static const uint8_t MOSI_LoRa = 10;
//static const uint8_t MISO_LoRa = 11;
//static const uint8_t RST_LoRa = 12;
//static const uint8_t BUSY_LoRa = 13;
//static const uint8_t DIO1_LoRa = 14;
//
//It is also recommended to redefine Arduino default SPI-1 and I2C-1 pins to OLED & LoRa pins as follow:
//
//static const uint8_t SDA = 17; // instead of 8;
//static const uint8_t SCL = 18; // instead of 9;
//
//static const uint8_t SS = 8; // instead of 10;
//static const uint8_t MOSI = 10; // instead of 11;
//static const uint8_t MISO = 11; // instead of 13;
//static const uint8_t SCK = 9; // instead of 12;

void setup() {
    //initialize Serial Monitor
    Serial.begin(115200);
    while (!Serial);
    Serial.println("LoRa Receiver");

    //setup LoRa transceiver module
    LoRa.setPins(ss, rst, dio0);

    //replace the LoRa.begin(---E-) argument with your location's frequency
    //433E6 for Asia
    //866E6 for Europe
    //915E6 for North America
    while (!LoRa.begin(915E6)) {
        Serial.println(".");
        delay(500);
    }
    // Change sync word (0xF3) to match the receiver
    // The sync word assures you don't get LoRa messages from other LoRa transceivers
    // ranges from 0-0xFF
    LoRa.setSyncWord(0xF3);
    Serial.println("LoRa Initializing OK!");
}

void loop() {
    // try to parse packet
    int packetSize = LoRa.parsePacket();
    if (packetSize) {
        // received a packet
        Serial.print("Received packet '");

        // read packet
        while (LoRa.available()) {
            String LoRaData = LoRa.readString();
            Serial.print(LoRaData);
        }

        // print RSSI of packet
        Serial.print("' with RSSI ");
        Serial.println(LoRa.packetRssi());
    }
}