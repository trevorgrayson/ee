// #include <ESP8266WiFi.h>
// #include <ESP8266HTTPClient.h>
// 
// #ifndef STASSID
// #define STASSID ""  // Your wifi network
// #define STAPSK  ""  // Your wifi password
// #endif
// 
// const char* host = "txtin.gs";
// const uint16_t port = 80;
// 
// const char* ssid     = STASSID;
// const char* password = STAPSK;
// 
// WiFiClient client;
// HTTPClient http;
// 
// bool connected = false;
// bool isOnline() {
//   connected = (WiFi.status() == WL_CONNECTED);
//   return connected;
// }
// 
// void wifiSetup() {
//   Serial.println("connecting.");
//   WiFi.mode(WIFI_STA);
//   WiFi.begin(ssid, password);
//   isOnline();
// }
// 
// String fetchStatus() {
//   String payload; 
//   if (!isOnline()) { return "not online."; }
//   if (!client.connect(host, port)) { return "no host."; }
//   
//   http.begin("http://txtin.gs/players/trevor/status");
// 
//   int httpCode = http.GET();
// 
//   if (httpCode == 200) {
//     payload = http.getString();
//     Serial.println(payload);
//   } else {
//     payload = String(httpCode);
//   }
//   http.end();
//   
//   return payload;
// }
