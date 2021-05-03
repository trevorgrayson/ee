#include "state.h"
#include "hardware/tempurature.h"

void render(struct State state);

void update(struct State *state) {
    state->tempurature = tempurature();
}

void tick(struct State *state) {
  update(state);
  render(*state);
}
