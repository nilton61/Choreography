#include <Arduino.h>
#include <Choreography.h>

stance red(); stance yellow();      //forward declaration of stances
Choreography colorBlink(red);       //instantiate with red as initial stance

enum {REDPIN = 14, YELLOWPIN};      //assign pins

void setup(){
    pinMode(REDPIN, OUTPUT);
    pinMode(YELLOWPIN, OUTPUT);
}//setup

void loop(){
    colorBlink.dance();             //run statemachine
}//loop

stance red(){
    digitalWrite(REDPIN, 1);
    digitalWrite(YELLOWPIN, 0);
    if(colorBlink.timeInStance() >= 1000) colorBlink.quickstep(yellow);
}//red

stance yellow(){
    digitalWrite(REDPIN, 0);
    digitalWrite(YELLOWPIN, 1);
    if(colorBlink.timeInStance() >= 1000) colorBlink.quickstep(yellow);
}//yellow