#include "state.h"
#include <stdio.h>

struct State state = {
    0.0,
    0.0
};

void render(struct State state) {
    printf(
      "temp: %4.2f humidity: %4.2f\n", 
      state.tempurature,
      state.humidity
   );
}

int main() {
    tick(&state);
    return 0;
}
