//
// Created by trevor on 10/3/2022.
//

#include "eink.h"


#include <Arduino.h>
// epd
#include "epd_driver.h"
#include "epd_highlevel.h"
#include "esp_sleep.h"

// font
#include "Firasans.h"


#define WAVEFORM EPD_BUILTIN_WAVEFORM

EpdiyHighlevelState hl;
// ambient temperature around device
int temperature = 20;
uint8_t *fb;
enum EpdDrawError err;

// CHOOSE HERE YOU IF YOU WANT PORTRAIT OR LANDSCAPE
// both orientations possible
EpdRotation orientation = EPD_ROT_PORTRAIT;
// EpdRotation orientation = EPD_ROT_LANDSCAPE;

int vref = 1100;

void display_center_message(const char* text) {
    // first set full screen to white
    epd_hl_set_all_white(&hl);

    int cursor_x = EPD_WIDTH / 2;
    int cursor_y = EPD_HEIGHT / 2;
    if (orientation == EPD_ROT_PORTRAIT) {
        // height and width switched here because portrait mode
        cursor_x = EPD_HEIGHT / 2;
        cursor_y = EPD_WIDTH / 2;
    }
    EpdFontProperties font_props = epd_font_properties_default();
    font_props.flags = EPD_DRAW_ALIGN_CENTER;
    epd_write_string(&FiraSans_12, text, &cursor_x, &cursor_y, fb, &font_props);

    epd_poweron();
    err = epd_hl_update_screen(&hl, MODE_GC16, temperature);
    delay(500);
    epd_poweroff();
    delay(1000);
}

void display_full_screen_left_aligned_text(const char* text) {
    EpdFontProperties font_props = epd_font_properties_default();
    font_props.flags = EPD_DRAW_ALIGN_LEFT;

    // first set full screen to white
    epd_hl_set_all_white(&hl);

    /************* Display the text itself ******************/
    // hardcoded to start at upper left corner
    // with bit of padding
    int cursor_x = 10;
    int cursor_y = 30;
    epd_write_string(&FiraSans_12, text, &cursor_x, &cursor_y, fb, &font_props);
    /********************************************************/

    /************ Battery percentage display ****************/
    // height and width switched here because portrait mode
    int battery_cursor_x = EPD_WIDTH - 30;
    int battery_cursor_y = EPD_HEIGHT - 10;
    if (orientation == EPD_ROT_PORTRAIT) {
        // switched x and y constants in portrait mode
        battery_cursor_x = EPD_HEIGHT - 10;
        battery_cursor_y = EPD_WIDTH - 30;
    }
    EpdFontProperties battery_font_props = epd_font_properties_default();
    battery_font_props.flags = EPD_DRAW_ALIGN_RIGHT;
    String battery_text = "OK";
    battery_text.concat("% Battery");
    epd_write_string(&FiraSans_12, battery_text.c_str(), &battery_cursor_x, &battery_cursor_y, fb, &battery_font_props);
    /********************************************************/

    epd_poweron();
    err = epd_hl_update_screen(&hl, MODE_GC16, temperature);
    delay(500);
    epd_poweroff();
    delay(1000);
}


void setupEPD() {
    // First setup epd to use later
    epd_init(EPD_OPTIONS_DEFAULT);
    hl = epd_hl_init(WAVEFORM);
    epd_set_rotation(orientation);
    fb = epd_hl_get_framebuffer(&hl);
    epd_clear();
}
