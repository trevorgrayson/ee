//
// Created by trevor on 10/22/2022.
//
// https://robojax.com/learn/arduino/?vid=robojax_ESP8266_intro_full

#include "client.h"

#include <stdio.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
//#include <HTTPClient.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>
#include "state.h"
#include "wificreds.h"  // TODO replace with env vars

#define USE_SERIAL Serial

char *response[1024];
StaticJsonDocument<1024> doc;

const char * host = "txtin.gs";
const uint16_t port = 443;

const char* calptrs[5];

ESP8266WiFiMulti wifiMulti;


void setupClient() {
    //TODO Tune this speed
    for(uint8_t t = 4; t > 0; t--) {
        // USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        // USE_SERIAL.flush();
        delay(1000);
    }

    WiFi.mode(WIFI_STA);
    wifiMulti.addAP(AP1_NAME, AP1_PASS);
    //    Serial.print("Waiting for WiFi... ");

    while(wifiMulti.run() != WL_CONNECTED) {
        // Serial.print(".");
        delay(500);
    }

    //    Serial.println("");
    //    Serial.println("WiFi connected");
    //    Serial.println("IP address: ");
    //    Serial.println(WiFi.localIP());
}

void request(State *state) {
    if((wifiMulti.run() != WL_CONNECTED)) {
       // USE_SERIAL.println("not connected");
       // return;  // TODO
    }

    WiFiClient client;
    HTTPClient http;

    // USE_SERIAL.print("[HTTP] begin...\n");
    // configure traged server and url
    http.begin(client, "http://txtin.gs/status"); //HTTP

    int httpCode = http.GET();
    if(httpCode > 0) {  // httpCode will be negative on error
        // HTTP header has been send and Server response header has been handled
        // USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);

        if(httpCode == HTTP_CODE_OK) {
            String payload = http.getString();

            DeserializationError error = deserializeJson(doc, payload);

            if (error) {
                sprintf(*(state->error), "deserializeJson() failed\0     ");
                Serial.print(F("deserializeJson() failed: "));
                Serial.println(error.f_str());
                return;
            }


            const char* metar = doc["metar"];
            const long aqi = doc["aqi"];

            JsonArray doing = doc["doing"];
            for(int x=0;
                x < doing.size();
                x++) {
                const char *row = doing[x];
                state->todos[x] = (char*)row;
            }
            state->todos[doing.size()] = 0;

        }
    } else {
        sprintf(*(state->error), "HTTP %s\0", http.errorToString(httpCode).c_str());
        USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
    client.stop();
}
