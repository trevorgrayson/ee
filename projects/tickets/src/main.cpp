//
// Created by trevor on 1/25/26.
//
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "Adafruit_Thermal.h"

const char* ssid     = "YOUR_SSID";
const char* password = "YOUR_PASS";

ESP8266WebServer server(80);

// Thermal printer on hardware serial
Adafruit_Thermal printer(&Serial);

void printMarkdown(String text);
//void handleRoot();
//void handlePrint();

void handleRoot() {
    String page = R"rawliteral(
  <html>
  <h2>Tickets Printer</h2>
  <p>POST text to <b>/print</b></p>
  <p>Example curl:</p>
  <pre>curl -X POST http://tickets.local/print -d "text=Hello **World**"</pre>
  <h3>Markdown Supported</h3>
  <ul>
    <li># Header</li>
    <li>**bold**</li>
    <li>*italic*</li>
    <li>`code`</li>
    <li>---</li>
  </ul>
  </html>
  )rawliteral";

    server.send(200, "text/html", page);
}

void handlePrint() {
    if (!server.hasArg("text")) {
        server.send(400, "text/plain", "Missing text field");
        return;
    }

    String text = server.arg("text");
    printMarkdown(text);

    server.send(200, "text/plain", "Printed");
}

void printLine(String line) {
    printer.println(line);
}

void printMarkdown(String text) {
    printer.justify('L');
    printer.setSize('S');

    while (text.length()) {
        int nl = text.indexOf('\n');
        String line = (nl == -1) ? text : text.substring(0, nl);
        if (nl != -1) text = text.substring(nl + 1);
        else text = "";

        line.trim();

        // Header
        if (line.startsWith("# ")) {
            printer.setSize('L');
            printer.boldOn();
            printer.println(line.substring(2));
            printer.boldOff();
            printer.setSize('S');
            continue;
        }

        // Divider
        if (line == "---") {
            printer.println("------------------------------");
            continue;
        }

        // Inline formatting
        while (line.length()) {
            if (line.startsWith("**")) {
                printer.boldOn();
                line = line.substring(2);
                int end = line.indexOf("**");
                if (end >= 0) {
                    printer.print(line.substring(0, end));
                    printer.boldOff();
                    line = line.substring(end + 2);
                }
            }
            else if (line.startsWith("*")) {
                printer.inverseOn();
                line = line.substring(1);
                int end = line.indexOf("*");
                if (end >= 0) {
                    printer.print(line.substring(0, end));
                    printer.inverseOff();
                    line = line.substring(end + 1);
                }
            }
            else if (line.startsWith("`")) {
                printer.underlineOn();
                line = line.substring(1);
                int end = line.indexOf("`");
                if (end >= 0) {
                    printer.print(line.substring(0, end));
                    printer.underlineOff();
                    line = line.substring(end + 1);
                }
            }
            else {
                printer.print(line[0]);
                line = line.substring(1);
            }
        }

        printer.println();
    }

    printer.feed(3);
}

/*
main.cpp
*/

void setup() {
    Serial.begin(19200);          // Most thermal printers default here
    delay(500);
    printer.begin();

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }

    MDNS.begin("tickets");

    server.on("/", HTTP_GET, handleRoot);
    server.on("/print", HTTP_POST, handlePrint);
    server.begin();
}

void loop() {
    server.handleClient();
    MDNS.update();
}
