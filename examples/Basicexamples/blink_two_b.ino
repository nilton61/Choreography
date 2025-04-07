#include <Arduino.h>
#include <Choreography.h>

stance red(); stance yellow();      //forward declaration of stances
Choreography colorBlink(red);       //instantiate with red as initial stance

enum {REDPIN = 14, YELLOWPIN};      //assign pins

stance showRed(){                   //show red led only
    digitalWrite(REDPIN, 1);
    digitalWrite(YELLOWPIN, 0);
}//showRed

stance showYellow(){                //show yellow led only
    digitalWrite(REDPIN, 0);
    digitalWrite(YELLOWPIN, 1);
}//showYellow


void setup(){
  pinMode(REDPIN, OUTPUT);
  pinMode(YELLOWPIN, OUTPUT);
}//setup

void loop(){
  colorBlink.dance();               //run statemachine
}//loop

stance red(){
  colorBlink.sequence(1000, showYellow, yellow);
}//red

stance yellow(){
  colorBlink.sequence(1000, showRed, red);
}//yellow