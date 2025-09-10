//
// Created by trevor on 9/9/25.
//
#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>

/*Put your SSID & Password*/
const char* ssid = "NETGEAR62";  // Enter SSID here
const char* password = "elatedship325";  //Enter Password here
const char* hostname = "esp32";

WebServer server(80);

void handle_OnConnect() {
    server.send(200, "text/html", "<!DOCTYPE html><html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\"></head><body><h1>Hey there!</h1></body></html>");
}

void handle_NotFound(){
    server.send(404, "text/plain", "Not found");
}


void setup() {
    Serial.begin(115200);
    delay(100);

    Serial.println("Connecting to ");
    Serial.println(ssid);

    //connect to your local wi-fi network
    WiFi.begin(ssid, password);

    //check wi-fi is connected to wi-fi network
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected..!");

    // Initialize mDNS
    if (!MDNS.begin("esp32")) {   // Set the hostname to "esp32.local"
        Serial.println("Error setting up MDNS responder!");
        while(1) {
            delay(1000);
        }
    }
    Serial.println("mDNS responder started");

    server.on("/", handle_OnConnect);
    server.onNotFound(handle_NotFound);

    server.begin();
    Serial.println("HTTP server started");
}
void loop() {
    server.handleClient();
}
