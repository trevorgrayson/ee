const int BUTTON_PIN[3] = {34, 35, 39};

int buttonState[3];
int buttonStateLast[3] = {LOW, LOW, LOW};
unsigned long lastDebounceTime[3] = {0, 0, 0};  // the last time the output pin was toggled
unsigned long debounceDelay = 50;  

void buttonSetup() {
  pinMode(BUTTON_PIN[0], INPUT);
  pinMode(BUTTON_PIN[1], INPUT);
  pinMode(BUTTON_PIN[2], INPUT);
}

// fire once when depressed.
int buttonPressed(int button) {
  int reading = digitalRead(BUTTON_PIN[button]);
  if (reading != buttonStateLast[button]) {
    // reset the debouncing timer
    lastDebounceTime[button] = millis();
  }
  if ((millis() - lastDebounceTime[button]) > debounceDelay) {
    // if the button state has changed:
    if (reading != buttonState[button]) {
      buttonState[button] = reading;
      
      if(buttonState[button]) {
        return 1;
      }
    }
  }
  buttonStateLast[button] = reading;

  return 0;
  // return buttonState;
}
