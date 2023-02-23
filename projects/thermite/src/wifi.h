#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h>

#include "state.h"

ESP8266WiFiMulti wifi;

const uint32_t connectTimeoutMs = 5000;
const char* ssid = "";
const char* password = "";
String deviceID = "thermite-attic";

void wifiSetup() {
  WiFi.mode(WIFI_STA);
  wifi.addAP(ssid, password);
  wifi.addAP("", "");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("connected.");
}

void request(State state) {
  if (wifi.run(connectTimeoutMs) == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;
    String URL = "http://txtin.gs/things/?name=thermite&ip=1.1.1.1&temp=" + 
                 String(state.temp) + "&iteration=" + String(state.iteration);
    http.begin(client, URL); // Works with HTTP
    
    int httpCode = http.POST("");
    if (httpCode > 0) {
      String payload = http.getString();
      Serial.println(payload); // Print response
    }
    
    http.end();
  } 
}
