#include <IRremote.h>
// https://www.hackster.io/electroboy001/ir-transmitter-remote-using-arduino-94e906
// https://arduino-irremote.github.io/Arduino-IRremote/classIRsend.html

IRsend irsend;

#define REPEATS 5

#define UP 5
#define DOWN 6
#define LEFT 7
#define RIGHT 8
#define ENTER 51

#define PLAY 15
#define MENU 10

bool isPressed(int BTN) {
    return digitalRead(BTN) == LOW;
}

void tx(int code) {
    irsend.sendNEC(code, 32, REPEATS);
    delay(30);
}

void setup()
{
    Serial.begin(9600);
    pinMode(UP,INPUT_PULLUP); // button 1
    pinMode(DOWN,INPUT_PULLUP); // button 2
    pinMode(LEFT,INPUT_PULLUP); // button 3
    pinMode(RIGHT,INPUT_PULLUP); // button 4
    // add more number of lines in code utilise more pins
}


void loop() {

    if (isPressed(UP)) {
        irsend.sendNEC(0x34895725, 32);  // change these unique code to yours but in decimal
        delay(30);
    } else if (isPressed(DOWN)) {
        irsend.sendNEC(0x56874159, 32);
        delay(30);
    } else if (isPressed(LEFT)) {
        irsend.sendNEC(0x15467823, 32);
        delay(30);
    } else if (isPressed(RIGHT)) {
        irsend.sendNEC(0x25467823, 32);
        delay(30);
    } else {
        Serial.println("Nothing to send");
        delay(30);
    }

    delay(100);
}
