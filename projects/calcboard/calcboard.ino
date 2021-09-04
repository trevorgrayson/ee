long reg1 = 0;
long reg0 = 0;
char operatr = 0;


int isNum(char key) {
  if(key < 58 && key > 47) {
    return 1;
  }
  return 0;
}

int isOperator(char key) {
  if(key < 48 && key > 41) {
    return 1;
  }
  return 0;
}

void setup() {
  // make pin 2 an input and turn on the
  // pullup resistor so it goes high unless
  // connected to ground:
  Serial.begin(115200);
  pinMode(2, INPUT_PULLUP);
}

void loop() {
  char key = getKey();
  if(isNum(key)) {
    reg0 = reg0 * 10 + (key - 48);
    Serial.println(reg0);
  } else if(isOperator(key)) {
    switch(operatr) {
      case '*': 
        reg1 = reg1 * reg0;
        break;
      case '/': 
        reg1 = reg1 / reg0;
        break;
      case '+': 
        reg1 = reg1 + reg0;
        break;
      case '-': 
        reg1 = reg1 - reg0;
        break;
    }
    reg0 = 0;
    Serial.print("reg1: ");
    Serial.print(key);
    Serial.print(": ");
    Serial.println(reg1);
    operatr = key;
  } else if(key == '#') { // ENTER
    reg1 = reg0;
    reg0 = 0;
    Serial.println(reg0, reg1);
  }
    
}
