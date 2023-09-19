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
    //Serial.println("Server started");

    //,km, Print the IP address
    //receiptPrint(WiFi.localIP().toString().c_str());
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
    client.println("<form action=\"/\"><textarea name=body></textarea><input type=\"submit\"/> </form>");
    client.println("</html>");
}


void serverTick() {
    WiFiClient client = server.accept();
    // wait for a client (web browser) to connect
    if (client)
    {
        bool isGET = true;
        //Serial.println("\n[Client connected]");
        while (client.connected())
        {
            // read line by line what the client (web browser) is requesting
            if (client.available())
            {
                String line = client.readStringUntil('\r');
                isGET = line[0] == 'G';

            }
            while (client.available()) {
                // but first, let client finish its request
                // that's diplomatic compliance to protocols
                // (and otherwise some clients may complain, like curl)
                // (that is an example, prefer using a proper webserver library)
                if (isGET) {
                    client.read();
                    webform(client);
                    break;

                }

                String line = client.readStringUntil('\n');

                if (line.length() == 1 && line[0] == '\n')
                {
                    // client.println("received.");
                    break;
                }

                receiptPrint(line);
            }
            client.read();

            // close the connection:
            client.stop();
        }


        //Serial.println("[Client disconnected]");
    }


//    // Return the response
//    client.println("HTTP/1.1 200 OK");
//    client.println("Content-Type: text/html");
//    client.println(""); //  do not forget this one
//    client.println("<!DOCTYPE HTML>");
//    client.println("<html>");
//
//    client.print("received.");
//
////    client.println("<br><br>");
//    client.println("<form action=\"/\"><input type=\"text\" name=body/><input type=\"submit\"/> </form>");
////    client.println("Click <a href=\"/LED=OFF\">here</a> turn the LED on pin 2 OFF<br>");
//    client.println("</html>");
//    client.stop();
}
