#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <LittleFS.h>
#include <ArduinoJson.h>
#include <Adafruit_Thermal.h>
#include <SoftwareSerial.h>
#include <map>

// ===== WiFi credentials =====
const char* ssid = WIFI_SSID;
const char* password = WIFI_PASS;

// ===== Printer setup =====
SoftwareSerial printerSerial(2, 0); // TX, RX (RX unused)
Adafruit_Thermal printer(&printerSerial);

// ===== Web server =====
ESP8266WebServer server(80);

// ===== URL map (stored in flash) =====
std::map<String, String> fetchMap;
const char* MAP_FILE = "/fetch_map.json";

// ===== Landing Page =====
const char* htmlLanding = R"rawliteral(
<!DOCTYPE html><html>
<head><title>Ticket Printer</title>
<style>body{font-family:sans-serif;margin:2em}textarea{width:100%;height:200px}</style>
</head><body>
<h2>Ticket Printer Service</h2>
<ul>
<li><code>/print</code> — POST Markdown, JSON, or text to print</li>
<li><code>/fetch</code> — POST to store {id,url}, GET /fetch?id=... to fetch & print</li>
</ul>
<form action="/print" method="post">
<textarea name="data" placeholder="Enter text or markdown..."></textarea><br>
<input type="submit" value="Print!">
</form>
</body></html>
)rawliteral";

// ===== Markdown to Plain =====
String markdownToPlain(String md) {
    md.replace("# ", "\n== ");
    md.replace("## ", "\n- ");
    md.replace("* ", " • ");
    md.replace("**", "");
    md.replace("_", "");
    return md;
}

// ===== Print helper =====
void printText(const String& text) {
    printer.wake();
    printer.println(F("----- New Print -----"));
    printer.println(text);
    printer.feed(2);
    printer.sleep();
}

// ===== Save & Load Map =====
void saveFetchMap() {
    DynamicJsonDocument doc(1024);
    for (auto& pair : fetchMap)
        doc[pair.first] = pair.second;
    File f = LittleFS.open(MAP_FILE, "w");
    if (!f) { Serial.println("⚠️ Failed to open map file for writing"); return; }
    serializeJson(doc, f);
    f.close();
    Serial.println("💾 Fetch map saved.");
}

void loadFetchMap() {
    if (!LittleFS.exists(MAP_FILE)) {
        Serial.println("ℹ️ No saved map.");
        return;
    }
    File f = LittleFS.open(MAP_FILE, "r");
    if (!f) { Serial.println("⚠️ Failed to open map file."); return; }

    DynamicJsonDocument doc(1024);
    if (deserializeJson(doc, f)) {
        Serial.println("⚠️ Invalid map JSON.");
        f.close();
        return;
    }
    f.close();
    for (JsonPair kv : doc.as<JsonObject>())
        fetchMap[String(kv.key().c_str())] = kv.value().as<String>();
    Serial.printf("✅ Loaded %d URL(s)\n", fetchMap.size());
}

// ===== /print =====
void handlePrint() {
    String contentType = server.header("Content-Type");
    String body = server.arg("data");
    if (body == "") body = server.arg("plain");

    String output = body;
    if (contentType.indexOf("markdown") >= 0)
        output = markdownToPlain(body);
    else if (contentType.indexOf("json") >= 0)
        output = "JSON received:\n" + body;

    printText(output);
    server.send(200, "text/plain", "Printed successfully.\n");
}

// ===== /fetch POST =====
void handleFetchPost() {
    String body = server.arg("plain");
    if (body == "") { server.send(400, "text/plain", "Missing body"); return; }

    StaticJsonDocument<256> doc;
    if (deserializeJson(doc, body)) {
        server.send(400, "text/plain", "Invalid JSON");
        return;
    }
    String id = doc["id"] | "";
    String url = doc["url"] | "";
    if (id == "" || url == "") {
        server.send(400, "text/plain", "Missing id or url");
        return;
    }

    fetchMap[id] = url;
    saveFetchMap();
    server.send(200, "text/plain", "Stored " + id + " → " + url + "\n");
}

// ===== /fetch GET =====
void handleFetchGet() {
    String id = server.arg("id");
    if (id == "") { server.send(400, "text/plain", "Missing ?id="); return; }
    if (fetchMap.find(id) == fetchMap.end()) {
        server.send(404, "text/plain", "No URL for ID " + id);
        return;
    }

    String url = fetchMap[id];
    Serial.println("Fetching: " + url);

    String payload;
    int code = -1;

    if (url.startsWith("https://")) {
        WiFiClientSecure client;
        client.setInsecure();  // ✅ accept all certificates
        HTTPClient https;
        if (!https.begin(client, url)) {
            server.send(500, "text/plain", "HTTPS init failed");
            return;
        }
        code = https.GET();
        if (code == HTTP_CODE_OK) payload = https.getString();
        https.end();
    } else if (url.startsWith("http://")) {
        WiFiClient client;
        HTTPClient http;
        if (!http.begin(client, url)) {
            server.send(500, "text/plain", "HTTP init failed");
            return;
        }
        code = http.GET();
        if (code == HTTP_CODE_OK) payload = http.getString();
        http.end();
    } else {
        server.send(400, "text/plain", "URL must start with http:// or https://");
        return;
    }

    if (code != HTTP_CODE_OK) {
        server.send(500, "text/plain", "Fetch failed, code " + String(code));
        return;
    }

    printText(payload);
    server.send(200, "text/plain", "Fetched and printed " + id + ":\n" + payload);
}

// ===== Root =====
void handleRoot() { server.send(200, "text/html", htmlLanding); }

void setup() {
    Serial.begin(115200);
    printerSerial.begin(19200);
    printer.begin();

    Serial.println("\nMounting LittleFS...");
    if (!LittleFS.begin()) Serial.println("⚠️ LittleFS mount failed!");
    else loadFetchMap();

    Serial.println("Connecting WiFi...");
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print("."); }
    Serial.printf("\nConnected! IP: %s\n", WiFi.localIP().toString().c_str());

    if (MDNS.begin("ticket")) Serial.println("mDNS responder started: http://ticket.local/");

    server.on("/", HTTP_GET, handleRoot);
    server.on("/print", HTTP_POST, handlePrint);
    server.on("/fetch", HTTP_POST, handleFetchPost);
    server.on("/fetch", HTTP_GET, handleFetchGet);

    server.begin();
    Serial.println("✅ Server ready!");
}

void loop() {
    server.handleClient();
    MDNS.update();
}
