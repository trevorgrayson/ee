void updateStarted() {
  Serial.println("CALLBACK:  HTTP update process started");
  clear();
  print("started");
  viewRender();
}

void updateFinished() {
  Serial.println("CALLBACK:  HTTP update process finished");
  clear();
  print("finished");
  viewRender();
}

void updateProgress(int cur, int total) {
  Serial.printf("CALLBACK:  HTTP update process at %d of %d bytes...\n", cur, total);
  clear();
  print("updating");
  viewRender();
}

void updateError(int err) {
  Serial.printf("CALLBACK:  HTTP update fatal error code %d\n", err);
  clear();
  print("fatal");
  viewRender();
}


