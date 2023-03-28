#include "Napper.h"
#include<avr/sleep.h>
#include<avr/interrupt.h>

void initNapper() {
    set_sleep_mode(SLEEP_MODE_PWR_SAVE);
    sleep_enable();
}


void nap() {

}