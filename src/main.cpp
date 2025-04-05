  #include <Arduino.h>
  #include <Choreography.h>

  enum {RED, YELLOW, GREEN, NCOLOR};
  enum {REDPIN = 14, YELLOWPIN, GREENPIN, SWITCH};
  
  // Main machine
  stance forth(); stance back(); stance backAndForth();
  Choreography manager(forth);

  //Sub machine1, forward
  stance forth1(); stance forth2(); stance forth3();
  Choreography forthManager(forth1);

  // Sub machine2, backward
  stance back1(); stance back2(); stance back3();
  Choreography backManager(back1);

  stance bNf1(); stance bNf2(); stance bNf3(); stance bNf4();
  Choreography bNfManager(bNf1);

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
    Serial.begin(9600);
  }//setup

  void loop() {
    manager.dance();
  }//loop

  stance forth(){
    forthManager.dance();
    manager.sequence(4500, back);
  };

  stance back(){
    backManager.dance();
    manager.sequence(4500, backAndForth);
  };

  stance backAndForth(){
    bNfManager.dance();
    manager.sequence(4800, forth);
  };

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