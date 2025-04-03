#include <Arduino.h>
#include <Choreography.h>

// Implementera klassen
  Choreography::Choreography(stancePointer initialStance, unsigned long (*timeFn)()) {
    currentStance = initialStance;
    timeFunc = timeFn;
    timeStamp = timeFunc();
  }//constructor
  
  void Choreography::sequence(unsigned long interval, stancePointer nextStance) {
    if (timeFunc() - timeStamp >= interval) { //timecheck
      timeStamp = timeFunc();                 //ny timestamp
      currentStance = nextStance;           //byt tillstånd nästa varv
    }//timecheck
  }//sequence med nextStance
  
  // Kör setupFunc och byter sedan till nextStance efter angivet tidsintervall
  void Choreography::sequence(unsigned long interval, stancePointer setupFunc, stancePointer nextStance) {
    if (timeFunc() - timeStamp >= interval) {//timecheck
      setupFunc();                        // Kör setup-funktionen en gång
      timeStamp = timeFunc();               // ny timestamp
      currentStance = nextStance;         // byt tillstånd nästa varv
    }//timecheck
  }//sequence med setupFunc och nextStance
  
  void Choreography::dance() {
    currentStance();
  }//dance
  
  unsigned long Choreography::timeInStance() {
    return timeFunc() - timeStamp;
  }//timeInStance
  
  void Choreography::quickstep(stancePointer nextStance) {
    timeStamp = timeFunc();
    currentStance = nextStance;
  }//quickstep
  
  void Choreography::passodoble(stancePointer setupFunc, stancePointer nextStance) {
    setupFunc();              // Kör setup-funktionen en gång
    timeStamp = timeFunc();     // Uppdatera tidsstämpeln
    currentStance = nextStance; // Byt till nästa tillstånd
  }//passodoble
  