int todo_x = 0;
int todo_y = 0;

int metar_x = 0;
int metar_y = 520;

char tempBuffer[5];
char humidityBuffer[5];
char displayBuffer[50];
char velocityBuff[25];

// state util
int todoCount(State s) {
  return sizeof(state.todos)-1;
}

void splashScreen() {
  int cursor_x = todo_x;
  int cursor_y = todo_y;
  int metar_y = 50 * 10; // height x rows
  char *hello = "hello.";
  epd_poweron();
  epd_clear();
  // epd_draw_grayscale_image(area, (uint8_t *)logo_data);

  cursor_x = todo_x; cursor_y += 50;

  writeln((GFXfont *)&FiraSans, hello, &cursor_x, &cursor_y, NULL);
  cursor_x = todo_x; 
  cursor_y += 50;

  epd_poweroff();  // It will turn off the power of the ink screen, but cannot turn off the blue LED light.
}

void renderCalendar(State s) {
  int cursor_x = 560;
  int cursor_y = 0;
  int ii = 0;
  for(int ix=0; ix < min(todoCount(s), 9); ix++) {
    if(!state.calendar[ix]) break; 
    cursor_x = 560; cursor_y += 50;
    writeln((GFXfont *)&FiraSans, state.calendar[ix], &cursor_x, &cursor_y, NULL);
    ii++;
  }
}

void renderTodos(State s, int cursor_x, int cursor_y) {
  for(int x=0; x < min(todoCount(s), 5);  x++) {
    // FAILS if list is short.
    if(!state.todos[x]) break; 
    writeln((GFXfont *)&FiraSans, s.todos[x], &cursor_x, &cursor_y, NULL);
    cursor_x = todo_x; 
    writeln((GFXfont *)&FiraSans, "➸", &cursor_x, &cursor_y, NULL);
    cursor_y += 50;
  }
}

void renderAQI(State s) {
  int cursor_x = 0;
  int cursor_y = metar_y - 50;
  writeln((GFXfont *)&FiraSans, s.aqiStr, &cursor_x, &cursor_y, NULL);
}

void renderWX(State s) {
  int cursor_x = 100;
  int cursor_y = metar_y - 50;
  sprintf(tempBuffer, "         ", state.temp);
  sprintf(tempBuffer, "%4.1fC", state.temp);
  writeln((GFXfont *)&FiraSans, tempBuffer, &cursor_x, &cursor_y, NULL);
  cursor_x += 50;
  sprintf(humidityBuffer, "         ", state.humidity);
  sprintf(humidityBuffer, "%4.1f%%", state.humidity);
  writeln((GFXfont *)&FiraSans, humidityBuffer, &cursor_x, &cursor_y, NULL);
}

void renderVelocity(State s) {
  int cursor_x = 0;
  int cursor_y = metar_y - 100;
  sprintf(velocityBuff, ">d%.1f r%.1f", 
          //state.velocity.track, 
          state.velocity.daily, 
          state.velocity.required
          );
  writeln((GFXfont *)&FiraSans, velocityBuff, &cursor_x, &cursor_y, NULL);
}

void renderCount(State s) {
  int cursor_x = 350;
  int cursor_y = metar_y - 50;
  sprintf(displayBuffer, "%d", state.count);
  writeln((GFXfont *)&FiraSans, displayBuffer, &cursor_x, &cursor_y, NULL);
}

void renderMETAR(State s) {
  writeln((GFXfont *)&FiraSans, s.metar, &metar_x, &metar_y, NULL);  
}

/*
 * screen: 540 x 960
 */
void render(State s) {
  int cursor_x = todo_x;
  int cursor_y = todo_y;
  int metar_y = 50 * 10; // height x rows
  epd_poweron();
  epd_clear();
  
  // epd_draw_grayscale_image(area, (uint8_t *)logo_data);

  renderMETAR(s);
  renderAQI(s);
  renderWX(s);
  renderVelocity(s);
  //renderCount(s);

  renderCalendar(s);
  renderTodos(s, todo_x + 50, 50);
  
  epd_poweroff();  // It will turn off the power of the ink screen, but cannot turn off the blue LED light.
}
