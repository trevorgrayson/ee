//
// Created by trevor on 1/25/26.
//
// TODO: full content body print.
// TODO: Swapping pins may remove chinese
// TODO: OTA Updates
// check headers
//extern "C" {
//#include "user_interface.h"
//}

#define DEBUG_ESP_PORT Serial
#define NODEBUG_WEBSOCKETS
#define NDEBUG

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "Adafruit_Thermal.h"
#include <SoftwareSerial.h>
#include <OtaClient.h>

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASS;

ESP8266WebServer server(80);
// server.enableCORS(false);

OtaClient ota(
        "http://ota.pearl.st",
        "tkts",
        "1.0.0"
);

// Thermal printer on hardware serial
#define PrinterSerial Serial    //TODO: swapping pins may remove chinese.
//SoftwareSerial printerSerial(2, 0); // TX, RX (RX unused) -1

Adafruit_Thermal printer(&PrinterSerial);


void printMarkdown(String text);
//void handleRoot();
//void handlePrint();

void handleRoot() {
    String page = R"rawliteral(
  <html>
  <h2>Therm Printer</h2>
  <p>POST text to <b>/print</b></p>
  <p>Example curl:</p>
  <pre>curl -X POST http://tkts.local/print "Hello **World**"</pre>
  <pre>curl -X POST http://tkts.local/print --data-binary @ticket.txt</pre>
  <pre>printf "# Order 42\n---\n**Burger**\n*No onions*\n" \
| curl http://tkts.local/print --data-binary @-</pre>
  <pre>curl http://tkts.local/print \
  --data-binary $'# Order 42\n---\n**Burger**\n*No onions*\n'</pre>
  <h3>Markdown Supported</h3>
  <ul>
    <li># Header</li>
    <li>**bold**</li>
    <li>*italic*</li>
    <li>`code`</li>
    <li>---</li>
  </ul>

  <style>
    body { font-family: sans-serif; padding: 20px; }
    textarea { width: 100%; height: 300px; font-family: monospace; }
    button { padding: 10px 20px; font-size: 16px; margin-top: 10px; }
    .status { margin-top: 10px; }
  </style>

<h2>Ticket Sender</h2>

<textarea id="ticket">
*** ORDER #123 ***
Burger
Fries
Coke

Thank you!
</textarea>

<br>
<button onclick="sendTicket()">Send to Printer</button>

<div class="status" id="status"></div>

<script>
function sendTicket() {
  const body = document.getElementById("ticket").value;
  const status = document.getElementById("status");

  status.textContent = "Sending...";

  fetch("http://tkts.local/print", {   // ← change if needed
    method: "POST",
    headers: {
      "Content-Type": "text/plain"
    },
    body: body
  })
  .then(res => res.text())
  .then(text => {
    status.textContent = "Server response: " + text;
  })
  .catch(err => {
    status.textContent = "Error: " + err;
  });
}
</script>
  </html>
  )rawliteral";

    server.send(200, "text/html", page);
}

void handlePrint() {
//    if (!server.hasArg("text")) {
//        server.send(400, "text/plain", "Missing text field");
//        return;
//    }

    String text = server.arg("plain");
    text.replace("\\n", "\n");
    text.replace("\\r", "");

    printMarkdown(text);

    server.send(200, "text/plain", "Printed");
}

void printLine(String line) {
    printer.println(line);
}

void printerResetStyles() {
    printer.boldOff();
    printer.inverseOff();
    printer.underlineOff();
    printer.justify('L');
    printer.setSize('S');
}

void printMarkdown(String text) {
    printer.justify('L');
    printer.setSize('S');

    while (text.length()) {
        printerResetStyles();
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
            printerResetStyles();
            printer.println("");
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
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }

    ota.begin();
    ota.checkForUpdate();   // check at boot

    MDNS.begin("tkts");

    server.on("/", HTTP_GET, handleRoot);
    server.on("/print", HTTP_POST, handlePrint);
    server.begin();

    PrinterSerial.begin(9600);          // 19200 Most thermal printers default here
    Serial.setDebugOutput(false);
    system_set_os_print(0);

    delay(500);
    printer.begin();
}

void loop() {
    server.handleClient();
    MDNS.update();
}
