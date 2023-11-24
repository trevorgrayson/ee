//
// Created by trevor on 9/16/2023.
//

#include <Arduino.h>
#include "PrintServer.h"
#include "ESP8266WiFi.h"
#include "ThermalPrinter.h"

WiFiServer server(80);


void serverSetup() {
    // Start the server
    server.begin();

    Serial.print("Use this URL to connect: ");
    Serial.print("http://");
    Serial.print(WiFi.localIP());
    Serial.println("/");
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
            // renderHTML(client);
        }
    }

    client.stop();
}

void renderHTML(WiFiClient client) {
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println(""); //  do not forget this one
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");

    client.print("received.");

    client.println("<br><br>");
    client.println("<form action=\"/\"><input type=\"text\" name=body/><input type=\"submit\"/> </form>");
    client.println("Click <a href=\"/LED=OFF\">here</a> turn the LED on pin 2 OFF<br>");
    client.println("</html>");

}