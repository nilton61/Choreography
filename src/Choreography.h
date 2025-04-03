#ifndef CHOREOGRAPHY_H
#define CHOREOGRAPHY_H

typedef void stance();            //Tilståndsfunktion
typedef stance* stancePointer;    //Pekre till tillståndsfunkrion

class Choreography {
  private:
  stancePointer currentStance;  //Aktuellt tillstånd
  unsigned long timeStamp;      //Tidsstämpel
  unsigned long (*timeFunc)();  //Pekare till tidsfunktion

  public:
    Choreography(stancePointer initialStance, unsigned long (*timeFn)() = millis);
    void dance();                 //Anropar det aktuella tillståndet
    unsigned long timeInStance(); //Returnerar millisekunder i nuvarande tillstånd
    void quickstep(stancePointer nextStance); //Byter till nästa tillstånd
    void passodoble(stancePointer setupFunc, stancePointer nextStance);
    // Byter till nextStance efter angivet tidsintervall
    void sequence(unsigned long interval, stancePointer nextStance);
    // Kör setupFunc och byter sedan till nextStance efter angivet tidsintervall
    void sequence(unsigned long interval, stancePointer setupFunc, stancePointer nextStance);
};//Choreography

#endif // CHOREOGRAPHY_H