#include <Arduino.h>
#include <Choreography.h>

// Fördeklarera funktioner
#define LED_PIN 13
int ledState = LOW;

// Fördeklarera funktionerna
stance blink;

// Skapa instans med initial tillståndsfunktion
Choreography ledDancer(blink);

void setup() {
  pinMode(LED_PIN, OUTPUT);
}//setup

void loop() {
  ledDancer.dance();
}//loop

void change() {
  ledState = !ledState;  // Slå om LED-tillståndet  
  digitalWrite(LED_PIN, ledState);
}//change

void blink() {
  ledDancer.sequence(1000, change, blink);
}//blink