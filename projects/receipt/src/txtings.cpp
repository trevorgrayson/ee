//
// Created by Trevor Grayson on 6/24/23.
//
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
//#include <HTTPClient.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>
#include "WiFiConn.h"

#include "state.h"


char *response[1024];
StaticJsonDocument<1024> doc;

const char * host = "txtin.gs";
const uint16_t port = 443;

const char* calptrs[5];


void setupTxtings(void) {
}


void request(State *state) {
    if(!isConnected()) {
        return;
    }

    WiFiClient client;
    HTTPClient http;

//    Serial.println("begin txtings");
    // configure traged server and url
    http.begin(client, "http://txtin.gs/status"); //HTTP

    // start connection and send HTTP header
    int httpCode = http.GET();
//    Serial.println("GET sent");
    // httpCode will be negative on error
    if(httpCode > 0) {
        // HTTP header has been send and Server response header has been handled

        // file found at server
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

            JsonArray calendar = doc["calendar"];
            for(int x=0;
                x < calendar.size() && x < 10;  // sizeof(state->calendar));
                x++) {
                const char *row = calendar[x];
                state->calendar[x] = (char*)row;
            }
            state->calendar[calendar.size()] = 0;


            state->metar = (char*)metar;
            state->metar[45] = '\0';

            JsonObject velocity = doc["velocity"];
//          state->velocity.track = "x"; // (char)velocity["track"];
            state->velocity.daily = (float)velocity["daily"];
            state->velocity.required = (float)velocity["required"];

            // remove next line
            sprintf(state->aqiStr, "%d", aqi);

//            Serial.println(payload);
        }
    } else {
        sprintf(*(state->error), "HTTP %s\0", http.errorToString(httpCode).c_str());
        Serial.printf("[HTTP] GET... failed.");
        // Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
    client.stop();
}
