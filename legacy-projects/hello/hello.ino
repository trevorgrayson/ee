// int LED_BUILTIN = 22;


void setup() {
    Serial.begin(115200);
    Serial.println("start.");
    //pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    Serial.println("tick.");
    //digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    //digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
}
