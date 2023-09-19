//
// Created by trevor on 9/17/2023.
//

#include "WiFiConn.h"

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
//#include <HTTPClient.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>
#include "wificreds.h"

ESP8266WiFiMulti wifiMulti;

void connectWiFi() {
    //TODO Tune this speed
    for(uint8_t t = 4; t > 0; t--) {
        delay(1000);
    }

//  wifiMulti.addAP("", "");
    WiFi.hostname("Receipt");
    wifiMulti.addAP(AP1_NAME, AP1_PASS);

    while(wifiMulti.run() != WL_CONNECTED) {
        delay(500);
    }
}

int isConnected()
{
    return (wifiMulti.run() == WL_CONNECTED);
}

void waitForWiFi() {
    while (!isConnected()) {
        delay(500);
        Serial.print(".");
    }
}