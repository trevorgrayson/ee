#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "wificreds.h"

const uint16_t port = 80;

const char* ssid     = STASSID;
const char* password = STAPSK;

WiFiClient client;
HTTPClient http;

bool connected = false;

bool isOnline() {
  // scan for nearby networks:
  int numSsid = WiFi.scanNetworks();
  if (numSsid == -1) {
    Serial.println("Couldn't get a wifi connection");
    while (true);
  }

  // print the list of networks seen:
  Serial.print("number of available networks:");
  Serial.println(numSsid);

  // print the network number and name for each network found:
  for (int thisNet = 0; thisNet < numSsid; thisNet++) {
    Serial.print(thisNet);
    Serial.print(") ");
    if (WiFi.SSID(thisNet) == "tell my wifi love her2.4") {
       Serial.print("tell my wifi found");
       return true;
    }
    if (WiFi.SSID(thisNet) == "dont you know") {
       Serial.print("dont you know found");
       return true;
    }
    Serial.print(WiFi.SSID(thisNet));
    Serial.print("\t");
    Serial.print(WiFi.RSSI(thisNet));
    Serial.print(" dBm");
    Serial.println("");
  }
  return false;
}

void wifiSetup() {
  Serial.println("connecting.");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  isOnline();
}
