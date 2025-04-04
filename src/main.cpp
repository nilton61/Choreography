  #include <Arduino.h>
  #include <Choreography.h>

  enum {RED, YELLOW, GREEN, NCOLOR};
  enum {REDPIN = 14, YELLOWPIN, GREENPIN, SWITCH};

  enum {FORTH, BACK, B_N_F, NPATTERN};

  typedef byte LedPattern[NCOLOR];
  const LedPattern lPattern[NCOLOR] = {
    {1, 0, 0},  // RED
    {0, 1, 0},  // YELLOW
    {0, 0, 1}   // GREEN
  };

  const LedPattern pinPattern = {REDPIN, YELLOWPIN, GREENPIN};

 
  stance forth();
  stance back();
  stance backAndForth();
  Choreography manager(forth, micros);

  stance forth1();
  stance forth2();
  stance forth3();
  Choreography forthManager(forth1, micros);

  stance back1();
  stance back2();
  stance back3();
  Choreography backManager(back1, micros);

  stance bNf1();
  stance bNf2();
  stance bNf3();
  stance bNf4();
  stance bNf5();
  Choreography bNfManager(bNf1, micros);

  stance showRED(){
    digitalWrite(REDPIN, 1);
    digitalWrite(YELLOWPIN, 0);
    digitalWrite(GREENPIN, 0);
  }

  stance showYELLOW(){
    digitalWrite(REDPIN, 0);
    digitalWrite(YELLOWPIN, 1);
    digitalWrite(GREENPIN, 0);
  }

  stance showGREEN(){
    digitalWrite(REDPIN, 0);
    digitalWrite(YELLOWPIN, 0);
    digitalWrite(GREENPIN, 1);
  }

  void setup() {
    pinMode(REDPIN, OUTPUT);
    pinMode(YELLOWPIN, OUTPUT);
    pinMode(GREENPIN, OUTPUT);
    pinMode(SWITCH, INPUT);
  }//setup

  void loop() {
    forthManager.dance();
  }//loop

  stance forth(){};
  stance back(){};
  stance backAndForth(){};
  stance forth1(){
    forthManager.sequence(500000, showRED, forth2);
  };

  stance forth2(){
    forthManager.sequence(500000, showYELLOW, forth3);
  };

  stance forth3(){
    forthManager.sequence(500000, showGREEN, forth1);
  };
  stance back1(){};
  stance back2(){};
  stance back3(){};
  stance bNf1(){};
  stance bNf2(){};
  stance bNf3(){};
  stance bNf4(){};
  stance bNf5(){};