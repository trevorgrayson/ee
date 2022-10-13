#include <Arduino.h>

// esp32 sdk imports
#include "esp_heap_caps.h"
#include "esp_log.h"

// epd
#include "epd_driver.h"
#include "epd_highlevel.h"

// battery
#include <driver/adc.h>
#include "esp_adc_cal.h"

// deepsleep
#include "esp_sleep.h"

// font
#include "Firasans.h"
#include "epd_n2h.h"
#include "eink.h"


/**
 * RTC Memory var to get number of wakeups via wakeup source button
 * For demo purposes of rtc data attr
**/
RTC_DATA_ATTR int pressed_wakeup_btn_index;

/**
 * That's maximum 30 seconds of runtime in microseconds
 */
int64_t maxTimeRunning = 30000000;


void setup() {
    Serial.begin(115200);

    setupEPD();

    /* Non deepsleep wakeup source button interrupt caused start e.g. reset btn */
    Serial.println("Woken up by reset button or power cycle");
    const char* message = "Hello! You shook me all night long.\nIn 30s I will go to deepsleep";
    display_center_message(message);
}

void loop()
{
    /*
    * Shutdown device after 30s always to conserve battery.
    * Basically almost no battery usage then until next wakeup.
    */
    if (esp_timer_get_time() > maxTimeRunning) {
        Serial.println("Max runtime of 30s reached. Forcing deepsleep now to save energy");
        display_center_message("Sleeping now.\nWake me up from deepsleep again\nwith the first button on my side");
        delay(1500);

        start_deep_sleep_with_wakeup_sources();
    }
}