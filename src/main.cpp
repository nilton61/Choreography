#include <Arduino.h>
#include <Choreography.h>

enum {RED, YELLOW, GREEN, NCOLOR};
enum {REDPIN = 14, YELLOWPIN, GREENPIN};

// 
stance redBlink();
stance yellowBlink();
stance greenBlink();

// Skapa instans med initial tillståndsfunktion och micros som tidsbas
Choreography blinker[NCOLOR] = {
  Choreography(redBlink, micros),
  Choreography(yellowBlink, micros),
  Choreography(greenBlink, micros)
};

void setup() {
  pinMode(REDPIN, OUTPUT);
  pinMode(YELLOWPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
}//setup

void loop() {
  for (byte c = RED; c < NCOLOR; c++) {
    blinker[c].dance();
  }
}//loop

stance changeRed(){
  digitalWrite(REDPIN, !digitalRead(REDPIN));
}//changeRed

stance changeYellow() {
  digitalWrite(YELLOWPIN, !digitalRead(YELLOWPIN));
}//changeYellow

stance changeGreen() {
  digitalWrite(GREENPIN, !digitalRead(GREENPIN));
}//changeGreen

// Impelementing state functions
stance redBlink() {
  blinker[RED].sequence(809989, changeRed, redBlink);
}//redBlink

stance yellowBlink() {
  blinker[YELLOW].sequence(1310867, changeYellow, yellowBlink);
}//yellowBlink

stance greenBlink() {
  blinker[GREEN].sequence(2120753, changeGreen, greenBlink);
}//greenBlink