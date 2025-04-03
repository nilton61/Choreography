# Example of a paralell state machine

In this example we have 3 separate state machines. They are implemented in an array of 3 instances of Choreography called blinker.
We have extensive use of enums to avoid numeric litterals so the instances are called blinker[RED], blinker[YELLOW], blinker[GREEN]. Each statemachine has a single state that transfers to iself att different microsekond intervalls. These intervalls are primenumbers chosen to give a very long pattern repetition period of about 26 days.

## Code structure

- lines 1 - 2: Include header files for arduino framework and Choreography library
- lines 4 - 5: enum declarations for colors and led pins. Red is 14, yellow is 15, green is 16
- lines 8 - 10: Declare state functions, its a good habit to declare functions before implementing them since this allows them to be called in any order. Many state machines are cyclical in nature 
- lines 13 - 16: instanciation of the 3 state machines. Placing them in an array facilitates the calling in a for-loop
- lines 19 - 23: Arduino setup function. Setting the 3 led pins as outputs. Using the enums above lets us avoid numeric litterals
- lines 25 - 29: Arduino loop function. all 3 state machines vill be calles repeatedly by a for-loop inside the arduino main loop
- lines 31 - 41: functions to toggle leds. Again numeric values have been replaced by symbolic enums
- lines 43 - 54: Impelementing state functions. they make use of the sequence pattern(delay(us), setUpfunction, newstate)