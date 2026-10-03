#ifndef BOARD_HAS_PSRAM
#error "Please enable PSRAM."
#endif

#include <Arduino.h>
#include <WiFi.h>

#include "firasans.h"
#include "epd_driver.h"
#include "TxtingStatusClient.h"

#ifndef WIFI_SSID
#define WIFI_SSID ""
#endif

#ifndef WIFI_PASSWORD
#define WIFI_PASSWORD ""
#endif

#ifndef STATUS_URL
#define STATUS_URL "http://txtin.gs/status"
#endif

namespace {

constexpr uint32_t kWifiConnectTimeoutMs = 30000;
constexpr uint32_t kRefreshIntervalMs = 300000;
constexpr int kTextLeft = 72;
constexpr int kHeaderY = 96;
constexpr int kBodyStartY = 196;
constexpr int kLineHeight = 42;
constexpr size_t kWrapColumns = 28;
constexpr size_t kMaxVisibleLines = 12;

txtingstatus::Client status_client(STATUS_URL);
txtingstatus::Snapshot last_snapshot;
uint32_t next_refresh_at = 0;

bool hasWiFiCredentials() {
  return strlen(WIFI_SSID) > 0;
}

String trimCopy(String value) {
  value.trim();
  return value;
}

void writeLine(const String& text, int y) {
  int cursor_x = kTextLeft;
  int cursor_y = y;
  writeln((GFXfont*)&FiraSans, (char*)text.c_str(), &cursor_x, &cursor_y, nullptr);
}

size_t measureWrappedLines(const String& text) {
  size_t count = 0;
  String remaining = trimCopy(text);
  while (remaining.length() > 0) {
    size_t take = remaining.length();
    if (take > kWrapColumns) {
      take = kWrapColumns;
      while (take > 0 && remaining.charAt(take) != ' ') {
        --take;
      }
      if (take == 0) {
        take = kWrapColumns;
      }
    }
    remaining = trimCopy(remaining.substring(take));
    ++count;
  }
  return count;
}

size_t drawWrappedText(const String& text, int start_y, size_t max_lines) {
  size_t lines_drawn = 0;
  String remaining = trimCopy(text);
  int y = start_y;

  while (remaining.length() > 0 && lines_drawn < max_lines) {
    size_t take = remaining.length();
    if (take > kWrapColumns) {
      take = kWrapColumns;
      while (take > 0 && remaining.charAt(take) != ' ') {
        --take;
      }
      if (take == 0) {
        take = kWrapColumns;
      }
    }

    const String line = trimCopy(remaining.substring(0, take));
    writeLine(line, y);
    remaining = trimCopy(remaining.substring(take));
    y += kLineHeight;
    ++lines_drawn;
  }

  return lines_drawn;
}

void renderDashboard(const String& headline, const String& subhead, const txtingstatus::Snapshot& snapshot) {
  epd_poweron();
  epd_clear();

  writeLine("TXTIN.GS", kHeaderY);
  writeLine(headline, kHeaderY + kLineHeight);
  //writeLine(subhead, kHeaderY + (kLineHeight * 2));

  int y = kBodyStartY;
  size_t remaining_lines = kMaxVisibleLines;

  if (snapshot.ok && snapshot.doing_count > 0) {
    for (size_t index = 0; index < snapshot.doing_count && remaining_lines > 0; ++index) {
      const String item = String(String(index + 1) + ". " + snapshot.doing[index]);
      const size_t lines_needed = measureWrappedLines(item);
      const size_t lines_to_draw = lines_needed > remaining_lines ? remaining_lines : lines_needed;
      const size_t lines_drawn = drawWrappedText(item, y, lines_to_draw);
      y += static_cast<int>(lines_drawn * kLineHeight) + 8;
      remaining_lines = lines_drawn >= remaining_lines ? 0 : remaining_lines - lines_drawn;
    }
  } else if (snapshot.ok) {
    writeLine("Nothing is currently marked doing.", y);
    y += kLineHeight;
  } else {
    writeLine("Fetch failed.", y);
    y += kLineHeight;
    if (snapshot.error.length() > 0) {
      drawWrappedText(snapshot.error, y, remaining_lines > 1 ? remaining_lines - 1 : 1);
    }
  }

  if (snapshot.truncated_count > 0 && remaining_lines > 0) {
    writeLine("+" + String(snapshot.truncated_count) + " more items not shown", y);
  }

  epd_poweroff_all();
}

bool connectWiFi() {
  if (WiFi.status() == WL_CONNECTED) {
    return true;
  }

  if (!hasWiFiCredentials()) {
    last_snapshot = txtingstatus::Snapshot{};
    last_snapshot.error = "Set WIFI_SSID and WIFI_PASSWORD in platformio.ini.";
    return false;
  }

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  const uint32_t started_at = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - started_at < kWifiConnectTimeoutMs) {
    delay(250);
  }

  if (WiFi.status() != WL_CONNECTED) {
    last_snapshot = txtingstatus::Snapshot{};
    last_snapshot.error = "WiFi connection timed out.";
    return false;
  }

  return true;
}

void refreshDisplay() {
  if (!connectWiFi()) {
    renderDashboard("doing", "Wi-Fi unavailable", last_snapshot);
    return;
  }

  txtingstatus::Snapshot snapshot;
  if (status_client.fetchDoing(snapshot)) {
    last_snapshot = snapshot;
    renderDashboard("doing", "Current queue", last_snapshot);
    return;
  }

  last_snapshot = snapshot;
  renderDashboard("doing", "Unable to refresh", last_snapshot);
}

}  // namespace

void setup() {
  Serial.begin(115200);
  delay(1000);
  epd_init();

  last_snapshot.error = "Booting.";
  renderDashboard("doing", "Starting up", last_snapshot);
  refreshDisplay();
  next_refresh_at = millis() + kRefreshIntervalMs;
}

void loop() {
  if (millis() >= next_refresh_at) {
    refreshDisplay();
    next_refresh_at = millis() + kRefreshIntervalMs;
  }

  delay(250);
}
