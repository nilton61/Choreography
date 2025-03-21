#include <Arduino.h>

unsigned long previousMillis = 0;
const long interval = 1000;
bool ledState = LOW;

void setup() {
  Serial.begin(9600);
  Serial.println("NodeMCU starting up...");
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    ledState = !ledState;
    digitalWrite(LED_BUILTIN, ledState);
    Serial.println(ledState ? "LED on" : "LED off");
  }
  
  // Här kan andra uppgifter utföras utan att blockeras
}