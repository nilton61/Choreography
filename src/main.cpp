#include <Arduino.h>

typedef void stance();            //Tilståndsfunktion
typedef stance* stancePointer;    //Pekre till tillståndsfunkrion

class Choreography {
  private:
    stancePointer currentStance;  //Aktuellt tillstånd
    unsigned long timeStamp;      //Tidsstämpel

  public:
    Choreography(stancePointer initialStance);
    void dance();                 //Anropar det aktuella tillståndet
    unsigned long timeInStance(); //Returnerar millisekunder i nuvarande tillstånd
    void quickstep(stancePointer nextStance); //Byter till nästa tillstånd
    void passodoble(stancePointer setupFunc, stancePointer nextStance);
    // Byter till nextStance efter angivet tidsintervall
    void sequence(unsigned long interval, stancePointer nextStance);
    // Kör setupFunc och byter sedan till nextStance efter angivet tidsintervall
    void sequence(unsigned long interval, stancePointer setupFunc, stancePointer nextStance);
};//Choreography

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

// Fördeklarera funktioner
#define LED_PIN 13
int ledState = LOW;

// Fördeklarera funktionerna
stance blink;

// Skapa instans med initial tillståndsfunktion
Choreography ledDancer(blink);

void setup() {
  pinMode(LED_PIN, OUTPUT);
}//setup

void loop() {
  ledDancer.dance();
}//loop

void change() {
  ledState = !ledState;  // Slå om LED-tillståndet  
  digitalWrite(LED_PIN, ledState);
}//change

void blink() {
  ledDancer.sequence(1000, change, blink);
}//blink