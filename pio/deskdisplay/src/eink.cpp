//
// Created by trevor on 10/3/2022.
//
// eink config: https://epdiy.readthedocs.io/en/latest/api.html
// 540X960

/***************************************************\
 * > todo1                             10 AM standup
 * > todo2                             10 AM standup
 * > todo3                             10 AM standup
 * > todo4                             10 AM standup
 * > todo5                             10 AM standup
 *
 *
 * velocity
 * KSMO 211503Z 10010 XXXXXXXXXXXXXXXXXXXXXXXXXX
 ****************************************************/

#include "../include/eink.h"
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
#include "font.h"
#include "../include/epd_n2h.h"

#define WAVEFORM EPD_BUILTIN_WAVEFORM

#define HEIGHT 540
#define WIDTH 960
#define TOP 30
#define LINE_HEIGHT 10

// state util
int todoCount(State state) {
    return sizeof(state.todos)-1;
}

int metar_x = 0;
int metar_y = 520;

char tempBuffer[5];
char humidityBuffer[5];
char displayBuffer[50];
char velocityBuff[25];

EpdiyHighlevelState hl;
// ambient temperature around device // epd_ambient_temperature
int temperature = 20;
uint8_t *fb;
enum EpdDrawError err;

// CHOOSE HERE YOU IF YOU WANT PORTRAIT OR LANDSCAPE
// both orientations possible
// EpdRotation orientation = EPD_ROT_PORTRAIT;
EpdRotation orientation = EPD_ROT_INVERTED_LANDSCAPE;

int vref = 1100;

float get_temp() {
    epd_poweron();
    return epd_ambient_temperature();
}

void update() {
    // can avoid turning on and off for each iteration.
    epd_poweron();
    err = epd_hl_update_screen(&hl, MODE_GC16, temperature);
    delay(500);
    epd_poweroff();
    delay(1000);
}

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
    epd_write_string(&DisplayFont, text, &cursor_x, &cursor_y, fb, &font_props);

    update();
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
    epd_write_string(&DisplayFont, text, &cursor_x, &cursor_y, fb, &font_props);
    /********************************************************/

    update();
}

void renderTodo(State state) {
    EpdFontProperties font_props = epd_font_properties_default();
    font_props.flags = EPD_DRAW_ALIGN_LEFT;

    int cursor_x = 0;
    int cursor_y = TOP;
    // "➸";

    for(int item=0; item < min(todoCount(state), 5);  item++) {
        if(!state.todos[item]) break;
        epd_write_string(&DisplayFont, state.todos[item], &cursor_x, &cursor_y, fb, &font_props);

        cursor_x = 0;
        cursor_y += LINE_HEIGHT;
    }
}

void renderCalendar(State state) {
    EpdFontProperties font_props = epd_font_properties_default();
    font_props.flags = EPD_DRAW_ALIGN_LEFT;
    int cursor_x = 560;
    int cursor_y = TOP;
    int ii = 0;
    for(int ix=0; ix < min(todoCount(state), 9); ix++) {
        if(!state.calendar[ix]) break;
        cursor_x = 560; cursor_y += LINE_HEIGHT;
        epd_write_string(&DisplayFont, state.calendar[ix], &cursor_x, &cursor_y, fb, &font_props);
        ii++;
    }
}

void renderAQI(State state) {
    EpdFontProperties font_props = epd_font_properties_default();
    font_props.flags = EPD_DRAW_ALIGN_LEFT;
    int cursor_x = 0;
    int cursor_y = metar_y - 50;
    epd_write_string(&DisplayFont, state.aqiStr, &cursor_x, &cursor_y, fb, &font_props);
}

void renderWX(State state) {
    EpdFontProperties font_props = epd_font_properties_default();
    font_props.flags = EPD_DRAW_ALIGN_LEFT;
    temperature = epd_ambient_temperature();

    int cursor_x = 0;
    int cursor_y = HEIGHT - 4 * LINE_HEIGHT;
    sprintf(tempBuffer, "         ", temperature);
    sprintf(tempBuffer, "%4.1fC", temperature);
    epd_write_string(&DisplayFont, tempBuffer, &cursor_x, &cursor_y, fb, &font_props);
//    cursor_x += 50;
//    sprintf(humidityBuffer, "         ", state.humidity);
//    sprintf(humidityBuffer, "%4.1f%%", state.humidity);
//    epd_write_string(&DisplayFont, humidityBuffer, &cursor_x, &cursor_y, fb, &font_props);
}

void renderMETAR(State state) {
    EpdFontProperties font_props = epd_font_properties_default();
    font_props.flags = EPD_DRAW_ALIGN_LEFT;

    int cursor_x = 0;
    int cursor_y = HEIGHT - LINE_HEIGHT;
    epd_write_string(&DisplayFont, state.metar, &cursor_x, &cursor_y, fb, &font_props);
}

void statusIcon() {
    EpdFontProperties font_props = epd_font_properties_default();
    font_props.flags = EPD_DRAW_ALIGN_LEFT;

    int cursor_x = WIDTH - LINE_HEIGHT;
    int cursor_y = HEIGHT - LINE_HEIGHT;
    epd_write_string(&DisplayFont, "...", &cursor_x, &cursor_y, fb, &font_props);
}

void setupEPD() {
    // First setup epd to use later
    epd_init(EPD_OPTIONS_DEFAULT);
    hl = epd_hl_init(WAVEFORM);
    epd_set_rotation(orientation);
    fb = epd_hl_get_framebuffer(&hl);
    epd_clear();
}

void thinking() {
    EpdFontProperties font_props = epd_font_properties_default();
    font_props.flags = EPD_DRAW_ALIGN_LEFT;
    temperature = epd_ambient_temperature();

    int cursor_x = WIDTH - 2 * LINE_HEIGHT;
    int cursor_y = HEIGHT - 4 * LINE_HEIGHT;
    epd_write_string(&DisplayFont, '0', &cursor_x, &cursor_y, fb, &font_props);
}

void tickEInk(State *state) {
    renderTodo(*state);
    renderCalendar(*state);
    renderMETAR(*state);

    state->temp = get_temp();
    renderWX(*state);

    update();
}
