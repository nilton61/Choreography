#include <Arduino.h>
#include <Choreography.h>

typedef enum :byte { RED, YELLOW, GREEN, NCOLOR} color;
typedef enum :byte {REDPIN = 14, YELLOWPIN, GREENPIN} pin;

// Fördeklarera funktionerna
stance redBlink;
stance yellowBlink;
stance greenBlink;

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
  for (byte i = 0; i < NCOLOR; i++) {
    blinker[i].dance();
  }
}//loop

void changeRed() {
  digitalWrite(REDPIN, !digitalRead(REDPIN));
}//changeRed

void changeYellow() {
  digitalWrite(YELLOWPIN, !digitalRead(YELLOWPIN));
}//changeYellow

void changeGreen() {
  digitalWrite(GREENPIN, !digitalRead(GREENPIN));
}//changeGreen

// Definitioner för stance-funktionerna
void redBlink() {
  blinker[RED].sequence(809989, [](){ changeRed(); }, redBlink);
}//redBlink

void yellowBlink() {
  blinker[YELLOW].sequence(1310867, [](){ changeYellow(); }, yellowBlink);
}//yellowBlink

void greenBlink() {
  blinker[GREEN].sequence(2120753, [](){ changeGreen(); }, greenBlink);
}//greenBlink