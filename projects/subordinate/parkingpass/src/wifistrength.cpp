//
// Created by trevor on 5/27/24.
//

#include "wifistrength.h"

#include <stdio.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
//#include <HTTPClient.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

#include "wificreds.h"  // TODO replace with env vars


ESP8266WiFiMulti wifiMulti;

void setupWifi() {
    //TODO Tune this speed
    for(uint8_t t = 4; t > 0; t--) {
        // USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        // USE_SERIAL.flush();
        delay(1000);
    }

    WiFi.mode(WIFI_STA);  // WIFI_AP_STA
    wifiMulti.addAP(AP1_NAME, AP1_PASS);

}

int strength()
{
    return WiFi.RSSI();
}

void waitForWifi() {
    //    Serial.print("Waiting for WiFi... ");
    while(wifiMulti.run() != WL_CONNECTED) {
        // Serial.print(".");
        delay(500);
    }
}

void announceWifi() {
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}
