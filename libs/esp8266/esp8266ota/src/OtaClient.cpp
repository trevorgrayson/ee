//
// Created by trevor on 2/2/26.
//
#include "OtaClient.h"
#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>
#include <WiFiClientSecureBearSSL.h>
#include <ArduinoJson.h>

OtaClient::OtaClient(const String& server,
                     const String& firmwareName,
                     const String& currentVersion)
        : _server(server),
          _firmwareName(firmwareName),
          _currentVersion(currentVersion) {}

void OtaClient::begin() {
    Serial.println("[OTA] Client initialized");
}

String OtaClient::buildCheckUrl() {
    return _server + "/ota/firmware?name=" + _firmwareName +
           "&version=" + _currentVersion;
}

void OtaClient::checkForUpdate() {
    std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);
    client->setInsecure();  // or set fingerprint/CA in production

    HTTPClient https;
    String url = buildCheckUrl();

    Serial.println("[OTA] Checking: " + url);

    if (!https.begin(*client, url)) {
        Serial.println("[OTA] HTTPS begin failed");
        return;
    }

    int httpCode = https.GET();

    if (httpCode == HTTP_CODE_NO_CONTENT) {
        Serial.println("[OTA] No update available");
        https.end();
        return;
    }

    if (httpCode != HTTP_CODE_OK) {
        Serial.printf("[OTA] Unexpected HTTP code: %d\n", httpCode);
        https.end();
        return;
    }

    String payload = https.getString();
    https.end();

    StaticJsonDocument<256> doc;
    DeserializationError err = deserializeJson(doc, payload);
    if (err) {
        Serial.println("[OTA] JSON parse failed");
        return;
    }

    String newVersion = doc["version"].as<String>();
    String binUrl = doc["url"].as<String>();

    Serial.println("[OTA] Update found → " + newVersion);
    performUpdate(binUrl);
}

bool OtaClient::performUpdate(const String& binUrl) {
    Serial.println("[OTA] Downloading firmware...");

    std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);
    client->setInsecure();

    t_httpUpdate_return ret = ESPhttpUpdate.update(*client, binUrl);

    switch (ret) {
        case HTTP_UPDATE_FAILED:
            Serial.printf("[OTA] Update failed (%d): %s\n",
                          ESPhttpUpdate.getLastError(),
                          ESPhttpUpdate.getLastErrorString().c_str());
            return false;

        case HTTP_UPDATE_NO_UPDATES:
            Serial.println("[OTA] No updates");
            return false;

        case HTTP_UPDATE_OK:
            Serial.println("[OTA] Update success — rebooting");
            return true;  // never actually returns (ESP reboots)
    }
    return false;
}
