#include <Arduino.h>
#include <Choreography.h>

enum {RED, YELLOW, GREEN, NCOLOR};                  //assign colors to values
enum {REDPIN = 14, YELLOWPIN, GREENPIN, SWITCH};    //assign pins

//Forward declararions
// Main machine
stance forth(); stance back(); stance backAndForth();
Choreography manager(forth);

//Sub machine1, forward
stance forth1(); stance forth2(); stance forth3();
Choreography forthManager(forth1);

// Sub machine2, backward
stance back1(); stance back2(); stance back3();
Choreography backManager(back1);

// Sub machine3 back and forth
stance bNf1(); stance bNf2(); stance bNf3(); stance bNf4();
Choreography bNfManager(bNf1);

//statemachine for debouncing input
stance stableLow(); stance transientHigh(); stance transientLow(); stance stableHigh();
Choreography debounce(stableHigh, micros);//SWITCH is active low

//display functions showing a single color
stance showRED(){
  digitalWrite(REDPIN, 1);
  digitalWrite(YELLOWPIN, 0);
  digitalWrite(GREENPIN, 0);
}//showRED

stance showYELLOW(){
  digitalWrite(REDPIN, 0);
  digitalWrite(YELLOWPIN, 1);
  digitalWrite(GREENPIN, 0);
}//showYELLOW

stance showGREEN(){
  digitalWrite(REDPIN, 0);
  digitalWrite(YELLOWPIN, 0);
  digitalWrite(GREENPIN, 1);
}//showGREEN

boolean oneShot = LOW;//used for signalling switch transition

void setup() {
  pinMode(REDPIN, OUTPUT);
  pinMode(YELLOWPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(SWITCH, INPUT);
  //Serial.begin(9600);
}//setup

void loop() {
  debounce.dance();
  manager.dance();
}//loop

//debounce stances
stance stableLow(){
  if(!digitalRead(SWITCH)) return;  //switch is low
  debounce.quickstep(transientHigh);
}//stableLow

stance transientHigh(){
  if(!digitalRead(SWITCH)) debounce.quickstep(transientLow);
  debounce.sequence(600, stableHigh);
}//transientHigh

stance stableHigh(){
  if(digitalRead(SWITCH)) return;
  oneShot = HIGH;//signal switch activated
  debounce.quickstep(transientLow);
}//stableHigh

stance transientLow(){
  oneShot = LOW;//reset oneshot
  if(digitalRead(SWITCH)) debounce.quickstep(transientHigh);
  debounce.sequence(600, stableLow);
}//transientLow

// Main machine
stance forth(){
  forthManager.dance();
  if(oneShot) manager.quickstep(back);
};//forth

stance back(){
  backManager.dance();
  if(oneShot) manager.quickstep(backAndForth);
};//back

stance backAndForth(){
  bNfManager.dance();
  if(oneShot) manager.quickstep(forth);
};//backAndForth

// Submachines, all very similar
stance forth1(){forthManager.sequence(500, showRED, forth2);};
stance forth2(){forthManager.sequence(500, showYELLOW, forth3);};
stance forth3(){forthManager.sequence(500, showGREEN, forth1);};
stance back1(){backManager.sequence(500, showGREEN, back2);};
stance back2(){backManager.sequence(500, showYELLOW, back3);};
stance back3(){backManager.sequence(500, showRED, back1);};
stance bNf1(){bNfManager.sequence(500, showRED, bNf2);};
stance bNf2(){bNfManager.sequence(500, showYELLOW, bNf3);};
stance bNf3(){bNfManager.sequence(500, showGREEN, bNf4);};
stance bNf4(){bNfManager.sequence(500, showYELLOW, bNf1);};