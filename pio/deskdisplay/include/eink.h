#include "state.h"

void setupEPD();
void display_center_message(const char* text);
void display_full_screen_left_aligned_text(const char* text);
void statusIcon();
void tickEInk(State *state);
float get_temp();
void thinking();