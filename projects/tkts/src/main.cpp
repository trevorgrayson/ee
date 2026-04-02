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
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <ESP8266mDNS.h>
#include "Adafruit_Thermal.h"
#include <SoftwareSerial.h>
#include <OtaClient.h>

const char* ssid     = WIFI_SSID;
const char* password = WIFI_PASS;

ESP8266WebServer server(80);
// server.enableCORS(false);

OtaClient ota("http://ota.pearl.st", "tkts", "1.0.0");

// Thermal printer on hardware serial
//SoftwareSerial printerSerial(2, 0); // TX, RX (RX unused) -1
#define PrinterSerial Serial    //TODO: different pins may remove chinese.

Adafruit_Thermal printer(&PrinterSerial);

void printMarkdown(String text);
void handleRoot();
void handlePrint();
void handleFetch();
void handleFetchOptions();

void handleRoot() {
    String page = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="utf-8" />
  <meta
    name="viewport"
    content="width=device-width, initial-scale=1, viewport-fit=cover"
  />
  <title>tkts.local</title>
  <style>
    :root {
      --bg: #f6f6f3;
      --panel: rgba(255,255,255,0.98);
      --text: #1f1f1a;
      --muted: #6f6c63;
      --line: rgba(0,0,0,0.08);
      --accent: #111111;
      --shadow: 0 12px 32px rgba(0,0,0,0.10);
      --radius: 18px;
      --safe-top: env(safe-area-inset-top, 0px);
      --safe-right: env(safe-area-inset-right, 0px);
      --safe-bottom: env(safe-area-inset-bottom, 0px);
      --safe-left: env(safe-area-inset-left, 0px);
    }

    * { box-sizing: border-box; }

    html, body {
      margin: 0;
      padding: 0;
      height: 100%;
      overflow: hidden;
      background: var(--bg);
      color: var(--text);
      font-family: ui-rounded, system-ui, -apple-system, BlinkMacSystemFont, "Segoe UI", sans-serif;
      -webkit-tap-highlight-color: transparent;
    }

    body {
      overscroll-behavior: none;
    }

    .app {
      height: 100dvh;
      display: grid;
      grid-template-rows: auto 1fr;
      padding:
        calc(8px + var(--safe-top))
        calc(10px + var(--safe-right))
        calc(10px + var(--safe-bottom))
        calc(10px + var(--safe-left));
      gap: 8px;
      overflow: hidden;
    }

    .topbar {
      display: flex;
      align-items: center;
      justify-content: space-between;
      gap: 10px;
      min-height: 40px;
      padding: 0 4px;
    }

    .title-wrap {
      min-width: 0;
      flex: 1;
    }

    .title {
      margin: 0;
      font-size: 0.98rem;
      line-height: 1.1;
      font-weight: 700;
      letter-spacing: -0.02em;
    }

    .subtitle {
      margin: 2px 0 0 0;
      font-size: 0.74rem;
      line-height: 1.1;
      color: var(--muted);
    }

    .status {
      white-space: nowrap;
      font-size: 0.75rem;
      color: var(--muted);
      background: var(--panel);
      border: 1px solid var(--line);
      padding: 6px 9px;
      border-radius: 999px;
    }

    .topbar-actions {
      display: inline-flex;
      align-items: center;
      gap: 8px;
      flex-wrap: wrap;
      justify-content: flex-end;
    }

    .pill-btn {
      border: 1px solid var(--line);
      background: var(--panel);
      color: var(--text);
      font-size: 0.72rem;
      padding: 6px 10px;
      border-radius: 999px;
      letter-spacing: 0.01em;
      cursor: pointer;
    }

    .pill-btn:active {
      background: rgba(0,0,0,0.06);
    }

    .editor-card {
      min-height: 0;
      height: 100%;
      background: var(--panel);
      border: 1px solid var(--line);
      border-radius: var(--radius);
      overflow: hidden;
      box-shadow: var(--shadow);
      display: grid;
      grid-template-rows: auto 1fr;
    }

    .editor-meta {
      display: flex;
      justify-content: space-between;
      align-items: center;
      gap: 12px;
      padding: 8px 12px;
      border-bottom: 1px solid var(--line);
      font-size: 0.76rem;
      color: var(--muted);
      flex: 0 0 auto;
    }

    .editor-scroll {
      min-height: 0;
      height: 100%;
      overflow-y: auto;
      overflow-x: hidden;
      -webkit-overflow-scrolling: touch;
      overscroll-behavior: contain;
    }

    textarea {
      display: block;
      width: 100%;
      min-height: 100%;
      border: 0;
      outline: 0;
      resize: none;
      background: transparent;
      color: var(--text);
      padding: 14px 14px 120px 14px;
      margin: 0;
      font: 400 19px/1.6 ui-monospace, SFMono-Regular, Menlo, Consolas, monospace;
      caret-color: #000;
      -webkit-appearance: none;
      appearance: none;
    }

    textarea::placeholder {
      color: #9a978f;
    }

    .toast {
      position: fixed;
      left: 50%;
      bottom: calc(96px + var(--safe-bottom));
      transform: translateX(-50%) translateY(10px);
      background: rgba(20,20,18,0.94);
      color: white;
      padding: 12px 14px;
      border-radius: 14px;
      font-size: 0.92rem;
      box-shadow: var(--shadow);
      opacity: 0;
      pointer-events: none;
      transition: 160ms ease;
      z-index: 1100;
      max-width: calc(100vw - 24px);
      text-align: center;
    }

    .toast.show {
      opacity: 1;
      transform: translateX(-50%) translateY(0);
    }

    @media (min-width: 720px) {
      .app {
        max-width: 760px;
        margin: 0 auto;
      }
    }
  </style>
</head>
<body>
  <div class="app">
    <header class="topbar">
      <div class="title-wrap">
        <h1 class="title">tkts.local printer</h1>
        <p class="subtitle">Editing</p>
      </div>
      <div class="topbar-actions">
        <button class="pill-btn" id="printBtn" type="button">Print</button>
        <button class="pill-btn" id="fetchBtn" type="button">Fetch</button>
        <div class="status" id="saveStatus">Saved</div>
      </div>
    </header>

    <section class="editor-card">
      <div class="editor-meta">
        <span id="charCount">0 chars</span>
        <span id="wordCount">0 words</span>
      </div>
      <div class="editor-scroll">
        <textarea
          id="editor"
          spellcheck="true"
          autocapitalize="sentences"
          autocomplete="off"
          autocorrect="on"
          placeholder="# Start writing"
        ></textarea>
      </div>
    </section>
  </div>

  <div class="toast" id="toast"></div>

  <script>
    (() => {
      const editor = document.getElementById("editor");
      const charCount = document.getElementById("charCount");
      const wordCount = document.getElementById("wordCount");
      const saveStatus = document.getElementById("saveStatus");
      const toast = document.getElementById("toast");

      const STORAGE_KEY = "mobile-markdown-editor-draft";

      function updateCounts() {
        const text = editor.value;
        charCount.textContent = `${text.length} chars`;
        const words = text.trim() ? text.trim().split(/\s+/).length : 0;
        wordCount.textContent = `${words} words`;
      }

      function setSavedState(label) {
        saveStatus.textContent = label;
      }

      let saveTimer = null;

      function persistDraft() {
        clearTimeout(saveTimer);
        setSavedState("Saving…");
        saveTimer = setTimeout(() => {
          localStorage.setItem(STORAGE_KEY, editor.value);
          setSavedState("Saved");
        }, 180);
      }

      function restoreDraft() {
        const saved = localStorage.getItem(STORAGE_KEY);
        if (saved !== null) editor.value = saved;
        updateCounts();
      }

      function showToast(message) {
        toast.textContent = message;
        toast.classList.add("show");
        clearTimeout(showToast._timer);
        showToast._timer = setTimeout(() => {
          toast.classList.remove("show");
        }, 1800);
      }

      async function fetchUrl(url) {
        const response = await fetch(`/fetch?url=${encodeURIComponent(url)}`);
        if (!response.ok) {
          throw new Error(`Fetch failed (${response.status})`);
        }
        return response.text();
      }

      async function printDocument() {
        const body = editor.value;
        if (!body.trim()) {
          showToast("Nothing to print");
          return;
        }

        showToast("Printing…");

        try {
          const response = await fetch("/print", {
            method: "POST",
            headers: {
              "Content-Type": "text/plain; charset=utf-8"
            },
            body: body
          });

          if (!response.ok) {
            throw new Error(`Print failed (${response.status})`);
          }

          showToast("Sent to printer");
        } catch (error) {
          console.error(error);
          showToast("Print failed");
        }
      }

      editor.addEventListener("input", () => {
        updateCounts();
        persistDraft();
      });

      document.getElementById("printBtn").addEventListener("click", printDocument);
      document.getElementById("fetchBtn").addEventListener("click", async () => {
        const url = prompt("Fetch URL");
        if (!url) return;
        showToast("Fetching…");
        try {
          const body = await fetchUrl(url);
          editor.value = body;
          updateCounts();
          persistDraft();
          showToast("Fetched");
        } catch (error) {
          console.error(error);
          showToast("Fetch failed");
        }
      });

      restoreDraft();
      if (!editor.value.trim()) setSavedState("New draft");
    })();
  </script>
</body>
</html>
  )rawliteral";
    /*
  <html>
  <h2>Therm Printer</h2>
  <p>POST text to <b>/print</b></p>
  <p>Example curl:</p>
  <pre>curl -X POST http://tkts.local/print --data-binary "Hello **World**"</pre>
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
    */

    server.send(200, "text/html", page);
}

void handlePrint() {
//    if (!server.hasArg("text")) {
//        server.send(400, "text/plain", "Missing text field");
//        return;
//    }
    printer.wake();
    delay(300);
    String text = server.arg("plain");
    text.replace("\\n", "\n");
    text.replace("\\r", "");

    printMarkdown(text);

    server.send(200, "text/plain", "Printed\n");
}

void addCorsHeaders() {
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.sendHeader("Access-Control-Allow-Methods", "GET, OPTIONS");
    server.sendHeader("Access-Control-Allow-Headers", "Content-Type");
    server.sendHeader("Access-Control-Max-Age", "600");
}

void handleFetchOptions() {
    addCorsHeaders();
    server.send(204, "text/plain", "");
}

void handleFetch() {
    addCorsHeaders();
    if (!server.hasArg("url")) {
        server.send(400, "text/plain", "Missing url");
        return;
    }

    String url = server.arg("url");
    if (!url.startsWith("http://") && !url.startsWith("https://")) {
        server.send(400, "text/plain", "Only http(s) URLs supported");
        return;
    }

    HTTPClient http;
    http.setTimeout(6000);

    bool isHttps = url.startsWith("https://");
    if (isHttps) {
        BearSSL::WiFiClientSecure client;
        client.setInsecure();
        if (!http.begin(client, url)) {
            server.send(502, "text/plain", "Bad URL");
            return;
        }
        int code = http.GET();
        if (code <= 0) {
            http.end();
            server.send(502, "text/plain", "Fetch failed");
            return;
        }
        String body = http.getString();
        http.end();
        server.send(code, "text/plain", body);
        return;
    }

    WiFiClient client;
    if (!http.begin(client, url)) {
        server.send(502, "text/plain", "Bad URL");
        return;
    }
    int code = http.GET();
    if (code <= 0) {
        http.end();
        server.send(502, "text/plain", "Fetch failed");
        return;
    }
    String body = http.getString();
    http.end();
    server.send(code, "text/plain", body);
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
    printer.println("");

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

void setup() {
    // Get WiFi log garbage out of the way.
    WiFi.mode(WIFI_STA);
    WiFi.hostname("tkts");
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }

    // Check for Updates
    ota.begin();
    ota.checkForUpdate();   // check at boot

    // Service
    MDNS.begin("tkts");

    server.on("/", HTTP_GET, handleRoot);
    server.on("/print", HTTP_POST, handlePrint);
    server.on("/fetch", HTTP_GET, handleFetch);
    server.on("/fetch", HTTP_OPTIONS, handleFetchOptions);
    server.begin();

    PrinterSerial.begin(9600);          // 19200 Most thermal printers default here
    Serial.setDebugOutput(false);
    system_set_os_print(0);

    // Ready Printer
    printer.begin();
}

void loop() {
    server.handleClient();
    MDNS.update();
}
