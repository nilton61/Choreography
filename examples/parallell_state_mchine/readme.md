# Example of a parallel state machine

In this example we have 3 separate state machines in order to exemplify how Choreography can be used to run several state machines independently without the need for threads or schedulers. They are implemented in an array of 3 instances of Choreography called blinker. Parallel state machines are useful in all situations where parallel processes have to be handled independently like reading sensors, updating displays, controlling actuators without blocking the main program logic.

We have extensive use of enums to avoid numeric literals so the instances are called blinker[RED], blinker[YELLOW], blinker[GREEN]. Each statemachine has a single state that transfers to itself at different microsecond intervals. These intervals are prime numbers chosen to give a very long pattern of repetition. The least common multiple of several prime numbers is their product giving a period of 809989 * 1310867 * 2120753 = 2.25e18 or about 26 days

## Code structure

### Preamble
- lines 1 - 2: Include header files for arduino framework and Choreography library

### Declarations
- lines 4 - 5: enum declarations for colors and led pins. Red is 14, yellow is 15, green is 16
- lines 8 - 10: Declare state functions, it's a good habit to declare functions before implementing them since this allows them to be called in any order. Many state machines are cyclical in nature 

### Instantiations
- lines 13 - 16: instantiation of the 3 state machines. Placing them in an array facilitates the calling in a for-loop
- lines 19 - 23: Arduino setup function. Setting the 3 led pins as outputs. Using the enums above lets us avoid numeric literals
- lines 25 - 29: Arduino loop function. all 3 state machines will be called repeatedly by a for-loop inside the arduino main loop
- lines 31 - 41: functions to toggle leds. Again numeric values have been replaced by symbolic enums
- lines 43 - 54: Implementing state functions. they make use of the sequence pattern(delay(us), setUpFunction, newState)

## Design decisions

### Use of enums
Enums provide a very elegant and convenient way of declaring symbolic constants. They are normally zero based but can be tweaked to specific values (enum {REDPIN = 14, YELLOWPIN, GREENPIN};) as long as all values in an enum are unique.

### Use of micros
Choreography has the option of using millis() (default) or micros() when instantiating. Here we chose micros to give the pattern finer granularity

### Use of array for machine instantiation
We chose to place the 3 instantiations in an array because this makes it very easy to select them in a for-loop or other code. Using enums in the for-loop aids readability

## Memory use

When compiling this example on an Arduino Nano we get:

Program:    1390 bytes (4.2% Full)
(.text + .data + .bootloader)

Data:         33 bytes (1.6% Full)
(.data + .bss + .noinit)

This shows that even with 3 parallel processes the memory use is minimal, which is crucial on platforms with limited resources like Arduino