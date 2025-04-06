#include <Arduino.h>
#include <Choreography.h>

// declare constants and variables
#define LED_PIN 13
int ledState = LOW;

// forward declare stances
stance blink();

// create single instance of Choreography
Choreography ledDancer(blink);

void setup() {
  pinMode(LED_PIN, OUTPUT);
}//setup

void loop() {
  ledDancer.dance();
  // loop is free for other code
}//loop

stance change() {
  ledState = !ledState;  //toggle LED state   
  digitalWrite(LED_PIN, ledState);
}//change

stance blink() {
  ledDancer.sequence(1000, change, blink);
}//blink