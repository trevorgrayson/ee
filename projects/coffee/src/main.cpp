//
// Created by jarvis@ipsumllc.com/ trevor on 6/29/25.
//
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <AccelStepper.h>
#include "wificreds.h"

// mdns module

// ==== WiFi Config ====
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

// ==== Pin Config ====
#define STEP_PIN D1
#define DIR_PIN  D2
#define RELAY_PIN D5
#define HEATER_PIN D6

// ==== Motor Config ====
#define MOTOR_INTERFACE_TYPE AccelStepper::DRIVER
#define STEPS_TO_ROTATE 200
#define RELAY_DELAY_MS 3000  // delay from rotation start

AccelStepper stepper(MOTOR_INTERFACE_TYPE, STEP_PIN, DIR_PIN);
ESP8266WebServer server(80);

// ==== Logic ====
void startCoffeeRoutine() {
    Serial.println("Starting coffee routine...");

    // Reset relay and heater
    digitalWrite(RELAY_PIN, LOW);
    digitalWrite(HEATER_PIN, LOW);

    // Start rotating motor
    stepper.setMaxSpeed(1000);
    stepper.setAcceleration(500);
    stepper.moveTo(STEPS_TO_ROTATE);

    unsigned long startTime = millis();
    bool relayTriggered = false;

    while (stepper.distanceToGo() != 0) {
        stepper.run();

        if (!relayTriggered && millis() - startTime >= RELAY_DELAY_MS) {
            Serial.println("Triggering relay.");
            digitalWrite(RELAY_PIN, HIGH);  // turn on relay
            relayTriggered = true;
        }
        delay(1);
    }

    // Ensure motor stopped
    Serial.println("Motor done. Turning on heater.");
    digitalWrite(HEATER_PIN, HIGH);  // begin heating
}

void handlePostCoffee() {
    if (server.method() == HTTP_POST) {
        server.send(200, "text/plain", "Coffee started!");
        startCoffeeRoutine();
    } else {
        server.send(405, "text/plain", "Method Not Allowed");
    }
}

void setup() {
    Serial.begin(115200);

    pinMode(RELAY_PIN, OUTPUT);
    pinMode(HEATER_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, LOW);
    digitalWrite(HEATER_PIN, LOW);

    // WiFi
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi...");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println(" Connected.");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    // Web Server
    server.on("/coffee", HTTP_POST, handlePostCoffee);
    server.begin();
    Serial.println("HTTP server started");
}

void loop() {
    server.handleClient();
}

