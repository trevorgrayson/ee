#ifndef SETUP_STATE

struct State {
  float tempurature;
  float humidity;
};

void update(struct State *state);
void render(struct State state);

void tick(struct State *state);

#endif 
