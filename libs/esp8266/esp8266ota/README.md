#include <OtaClient.h>

OtaClient ota(
"https://yourserver.com",
"ticket-printer",
"1.0.3"
);

void setup() {
Serial.begin(115200);
WiFi.begin("ssid", "pass");

    while (WiFi.status() != WL_CONNECTED) delay(200);

    ota.begin();
    ota.checkForUpdate();   // check at boot
}

void loop() {
// normal firmware logic
}

```asm
lib_deps =
    esp8266ota=symlink://../../libs/esp8266/esp8266ota
```

```asm
lib_deps =
    bblanchon/ArduinoJson
```