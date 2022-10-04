#include <Arduino.h>

// esp32 sdk imports
#include "esp_heap_caps.h"
#include "esp_log.h"

#include "epd_driver.h"
#include "epd_highlevel.h"

#include "eink.h"
#include "sleep.h"

void setup() {
    Serial.begin(115200);

    setupEPD();

    const char* message = "Hello! You shook me all night long.\nIn 30s I will go to deepsleep";
    display_center_message(message);
}

void loop()
{
    /*
    * Shutdown device after 30s always to conserve battery.
    * Basically almost no battery usage then until next wakeup.
    */
    consider_sleeping();
}