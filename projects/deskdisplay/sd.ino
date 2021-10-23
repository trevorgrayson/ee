#include <SPI.h>
#include <SD.h>

void detectSD() {
    char buf[128];
    /* https://github.com/espressif/arduino-esp32/tree/master/libraries/SD/examples */
    SPI.begin(SD_SCLK, SD_MISO, SD_MOSI);
    bool rlst = SD.begin(SD_CS);
    if (!rlst) {
        Serial.println("SD init failed");
        snprintf(buf, 128, "➸ No detected SdCard");
    } else {
        snprintf(buf, 128, "➸ Detected SdCard insert:%.2f GB", SD.cardSize() / 1024.0 / 1024.0 / 1024.0);
    }

    // writeln((GFXfont *)&FiraSans, buf, &cursor_x, &cursor_y, NULL);
}

void displayVoltage() {
    // When reading the battery voltage, POWER_EN must be turned on
    epd_poweron();
    uint16_t v = analogRead(BATT_PIN);
    float battery_voltage = ((float)v / 4095.0) * 2.0 * 3.3 * (vref / 1000.0);
    String voltage = "➸ Voltage :" + String(battery_voltage) + "V";
    Serial.println(voltage);

    Rect_t area = {
        .x = 200,
        .y = 460,
        .width = 320,
        .height = 50,
    };

    int cursor_x = 200;
    int cursor_y = 500;
    epd_clear_area(area);
    //writeln((GFXfont *)&FiraSans, (char *)voltage.c_str(), &cursor_x, &cursor_y, NULL);  
}
