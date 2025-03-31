# Choreography
A lightweight state machine library for arduino and similar microcontrollers

## Overview

Choreography provides an elegant and highly efficient framework for implementing state machines on resource-constrained platforms. With minimal overhead and an intuitive dance-inspired syntax, Choreography makes complex state management simple and readable.

## Features

- **Ultra-lightweight**: Optimized for performance on microcontrollers
- **Intuitive syntax**: Dance-themed naming conventions make code more readable
- **Multiple state machines**: Run several state machines in parallel
- **Built-in timing**: Easily implement timed state transitions
- **Simple setup patterns**: Special functions for initialization states
- **Non-blocking multitasking**: Achieve concurrent operations without RTOS overhead
- **Zero-blocking requirement**: Enforces good practices by requiring non-blocking code

## Basic Usage

```c
#include <Arduino.h>
#include <Choreography.h>

#define LED_PIN 13
int ledState = LOW;

stance blink;// Declare state function

//create state machine, set timebase to microseconds
Choreography ledDancer(blink, micros);

void setup() {
  pinMode(LED_PIN, OUTPUT);
}//setup

void loop() {
  ledDancer.dance();//run state machine
}//loop

void change() {
  ledState = !ledState;  // change led state  
  digitalWrite(LED_PIN, ledState);
}//change

void blink() {
  ledDancer.sequence(1000000, change, blink);
}//blink
```

## Advanced Features

### Setup Sequences with Passodoble

For states that need initialization, use the `passodoble` function:

```c
stance buttonPressed() {
  // Run the setup code once, then transition to the main state
  passodoble(displaySetup, displayRunning);
}

void displaySetup() {
  // Initialize display, runs once
  display.begin();
  display.clearScreen();
}

stance displayRunning() {
  // Regular operation of display
  display.showValue(sensorReading);
}
```

### Multiple State Machines

```c
Choreography buttonDancer;
Choreography displayDancer;
Choreography motorDancer;

void loop() {
  buttonDancer.dance();
  displayDancer.dance();
  motorDancer.dance();
}
```

## Design Philosophy

Choreography enforces non-blocking code patterns, which is essential for reliable operation on microcontrollers. Each stance must complete quickly, allowing other processes to run. This approach enables effective multitasking without the overhead of a real-time operating system.
> -This means: forget all blink examples that use delay and every other code that uses delay or loops

## License

[GNU GENERAL PUBLIC LICENSE Version 3](LICENSE)

## Contribution

Contributions are welcome! Please feel free to submit a Pull Request.
