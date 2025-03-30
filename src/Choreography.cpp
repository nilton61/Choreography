#include <Arduino.h>
#include <Choreography.h>

// Implementera klassen
Choreography::Choreography(stancePointer initialStance) {
    currentStance = initialStance;
    timeStamp = millis();
  }//Constructor
  
  void Choreography::sequence(unsigned long interval, stancePointer nextStance) {
    if (millis() - timeStamp >= interval) { //timecheck
      timeStamp = millis();                 //ny timestamp
      currentStance = nextStance;           //byt tillstånd nästa varv
    }//timecheck
  }//sequence med nextStance
  
  // Kör setupFunc och byter sedan till nextStance efter angivet tidsintervall
  void Choreography::sequence(unsigned long interval, stancePointer setupFunc, stancePointer nextStance) {
    if (millis() - timeStamp >= interval) {//timecheck
      setupFunc();                        // Kör setup-funktionen en gång
      timeStamp = millis();               // ny timestamp
      currentStance = nextStance;         // byt tillstånd nästa varv
    }//timecheck
  }//sequence med setupFunc och nextStance
  
  void Choreography::dance() {
    currentStance();
  }//dance
  
  unsigned long Choreography::timeInStance() {
    return millis() - timeStamp;
  }//timeInStance
  
  void Choreography::quickstep(stancePointer nextStance) {
    timeStamp = millis();
    currentStance = nextStance;
  }//quickstep
  
  void Choreography::passodoble(stancePointer setupFunc, stancePointer nextStance) {
    setupFunc();              // Kör setup-funktionen en gång
    timeStamp = millis();     // Uppdatera tidsstämpeln
    currentStance = nextStance; // Byt till nästa tillstånd
  }//passodoble
  