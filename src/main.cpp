#include <Arduino.h>

typedef void stance();            //Tilståndsfunktion
typedef stance* stancePointer;    //Pekre till tillståndsfunkrion

class Choreography {
  private:
    stancePointer currentStance;  //Aktuellt tillstånd
    unsigned long stanceStartTime;//Tidsstämpel
    
  public:
    Choreography(stancePointer initialStance);
    void dance();                 //Anropar det aktuella tillståndet
    unsigned long timeInStance(); //Returnerar millisekunder i nuvarande tillstånd
};//Choreography

Choreography::Choreography(stancePointer initialStance) {//Constructor
  currentStance = initialStance;  //Initialt tillstånd
  stanceStartTime = millis();     //Tidsstämpel
}//Constructor

void Choreography::dance() {
  currentStance();  //Anropa aktuellt tillstånd
}//dance

stance testFunction;
void testFunction(){
  Serial.println("Test function called");
}//testFunction


Choreography newbie(testFunction);

void setup() {
  Serial.begin(9600);
  newbie.dance();
}//setup()

void loop() {
  // Resten av koden
}//loop()
