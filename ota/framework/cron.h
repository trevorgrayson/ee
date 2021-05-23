int EPOCH, NOW;

#ifndef UPDATE_INTERVAL 
#define UPDATE_INTERVAL 5000
#endif


void cronSetup() {
  EPOCH = millis();
}

void cronTick() {
  NOW = millis();
}

bool shouldUpdate() {
  if ( (NOW - UPDATE_INTERVAL) > EPOCH ) {
    EPOCH = NOW;
    return true;
  }
  return false;
}
