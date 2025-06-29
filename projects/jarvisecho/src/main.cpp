//
// Created by jarvis@ipsumllc.com on 6/29/25.
//
#include <M5Unified.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "wificreds.h"
#include <esp_sr_wakenet.h>
#include <esp_mn_speech_commands.h>
#include <esp_audio_front_end.h>

#define WAKEWORD "Jarvis"
#define JARVIS_ENDPOINT "https://jarvis.pearl.st"

void connectWiFi() {
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("WiFi connected");
}

void sendToJarvis(const char* transcript) {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient https;
        https.begin(JARVIS_ENDPOINT);
        https.addHeader("Content-Type", "application/json");

        String payload = String("{\"command\":\"") + transcript + "\"}";
        int httpCode = https.POST(payload);
        Serial.printf("HTTP response: %d\n", httpCode);
        https.end();
    }
}

void setup() {
    M5.begin();
    Serial.begin(115200);
    connectWiFi();

    M5.Speaker.begin();
    M5.Speaker.setVolume(128);
    M5.Speaker.println("Listening for wake word: Jarvis");

    // Initialize wake word engine here (pseudo-code):
    // WakeNet.begin();  <-- You'll need to integrate the actual ESP-SR WakeNet APIs
}

void loop() {
    static bool triggered = false;

    // Pseudo code for wakeword detection:
    if (!triggered && detectWakeWord(WAKEWORD)) {
        triggered = true;
        M5.Speaker.println("Yes?");
        delay(500);

        // Record the next few seconds of speech
        String transcript = recordAndTranscribe(); // Implement or use a service
        Serial.println("Heard: " + transcript);
        sendToJarvis(transcript.c_str());
        triggered = false;
    }

    delay(100);
}
