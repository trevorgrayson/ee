//
// Created by trevor on 9/16/2023.
//

#include <Arduino.h>
#include "PrintServer.h"
#include "ESP8266WiFi.h"
#include "ThermalPrinter.h"

WiFiServer server(80);


void serverStart() {
    // Start the server
    server.begin();

    Serial.print("Use this URL to connect: ");
    Serial.print("http://");
    Serial.print(WiFi.localIP());
    Serial.println("/");
}

void serverStop() {
    server.stop();
}

void webform(WiFiClient client) {
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println(""); //  do not forget this one
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");

    client.print("<h1>Print Me:</h1>");
    client.println("<form method=\"POST\" action=\"/\"><textarea name=body></textarea><input type=\"submit\"/> </form>");
    client.println("</html>");
}

void serverTick() {
    WiFiClient client = server.accept();
    // wait for a client (web browser) to connect
    if (client)
    {
        bool isGET = true;
        // Serial.println("\n[Client connected]");
        while (client.connected())
        {
            // read line by line what the client (web browser) is requesting
            if (client.available())
            {
                String line = client.readStringUntil('\n');
                isGET = line[0] == 'G';
                if (isGET) {
                    client.read();
                    webform(client);
                    break;
                }
            }

            bool inBody = 1; //TODO
            while (client.available()) {
                String line = client.readStringUntil('\n');  // HTTP Protocol

                if (line.length() == 0) {
                    client.stop();
                    return;
                }
                // clear headers
                // if (line.length() == 0) // && line[0] == '\n')
                // {
                //  inBody = 1;
                // }

                if (inBody) {
                    client.println(line);
                    receiptPrint(line);
                }
            }

            client.read();
        }
    }

    client.stop();
}
