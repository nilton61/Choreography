#include <Arduino.h>
#include <Choreography.h>

// Implement Choreography class
  Choreography::Choreography(stancePointer initialStance, unsigned long (*timeFn)()) {
    currentStance = initialStance;            //initial state
    timeFunc = timeFn;                        //millis()(default) or micros
    timeStamp = timeFunc();                   //create timestamp
  }//constructor
  
  void Choreography::sequence(unsigned long interval, stancePointer nextStance) {
    if (timeFunc() - timeStamp >= interval) { //timecheck
      timeStamp = timeFunc();                 //new timestamp
      currentStance = nextStance;             //change state next scan cycle
    }//timecheck
  }//sequence med nextStance
  
  // Call setupFunction and the change state next scancycle
  void Choreography::sequence(unsigned long interval, stancePointer setupFunc, stancePointer nextStance) {
    if (timeFunc() - timeStamp >= interval) { //timecheck
      setupFunc();                            //run setupFunction only once
      timeStamp = timeFunc();                 //new timestamp
      currentStance = nextStance;             //change state next scan cycle
    }//timecheck
  }//sequence with setupFunc and nextStance
  
  void Choreography::dance() {
    currentStance();
  }//dance
  
  unsigned long Choreography::timeInStance() {
    return timeFunc() - timeStamp;            //calculate time overflow safe
  }//timeInStance
  
  void Choreography::quickstep(stancePointer nextStance) {
    timeStamp = timeFunc();                    //calculate time overflow safe
    currentStance = nextStance;
  }//quickstep
  
  void Choreography::passodoble(stancePointer setupFunc, stancePointer nextStance) {
    setupFunc();                              //run setupFunction only once
    timeStamp = timeFunc();                   //update timeStamp 
    currentStance = nextStance;               //change state next scan cycle
  }//passodoble
  