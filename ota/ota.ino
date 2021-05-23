/**
   httpUpdate.ino
   MAC: a0:20:a6:27:0b:b2

    Created on: 27.11.2015

*/

#include <Arduino.h>
#include "wificreds.h"

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>
#include "pins.h"
#include "ota.h"

void setup() {
  Serial.begin(115200);
  //Serial.setDebugOutput(true);
  viewSetup();
  clear();
  print("hello.");
  viewRender();

  Serial.println();

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  setupNetwork();
  print("starting...");
  viewRender();
}

void loop() {
  checkForUpdate();
  clear();
  print("v1.0.19");
  viewRender();
}
