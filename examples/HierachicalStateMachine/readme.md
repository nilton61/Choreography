# Example: Hierarchical State machine

In this example we are showing how Choreography can be used to implement hierarchical state machines. We have a main state machine with 3 states: forth, back, backAndForth. Each of the main states shows a diffrent pattern of blinking leds. Each of these patterns is a state machine of its own. The following diagram explains this:

```mermaid
stateDiagram-v2
    direction LR
    [*] --> forth
    forth --> back: oneShot
    back --> backAndForth: oneShot
    backAndForth --> forth: oneShot

    state forth {
        [*] --> forth1
        forth1 --> forth2: 500ms / showRED
        forth2 --> forth3: 500ms / showYELLOW
        forth3 --> forth1: 500ms / showGREEN
    }

    state back {
        [*] --> back1
        back1 --> back2: 500ms / showGREEN
        back2 --> back3: 500ms / showYELLOW
        back3 --> back1: 500ms / showRED
    }

    state backAndForth {
        [*] --> bNf1
        bNf1 --> bNf2: 500ms / showRED
        bNf2 --> bNf3: 500ms / showYELLOW
        bNf3 --> bNf4: 500ms / showGREEN
        bNf4 --> bNf1: 500ms / showYELLOW
    }
```

The trasitions between the main states are controlled by a user pushbutton switch which has its own state machine for debouncing. The debounce state machine communicates its actions via a boolean variable named oneShot, which is high exactly 1 arduino-loop cycle when pressed by the user. The time constant 600us is chosen to exceed one single bounce. The state diagram is as following

```mermaid
stateDiagram
  direction TB
  [*] --> stableHigh
  stableHigh --> transientLow: switch==low
  transientLow --> stableLow: t>600us
  stableLow --> transientHigh: switch==high
  transientHigh --> stableHigh: t>600us
  transientHigh --> transientLow: switch==low
  transientLow --> transientHigh: switch==high
```

## Code description

### Preamble

- lines 1-2: includes for Arduino and Choreography

### Enums

- lines 4-5: assign values to physical properties

### Forward declarations

- lines 8 - 10: main machine
- lines 12 - 14: forward sub machine
- lines 16 - 18: backward sub machine
- lines 20 - 22: back and forth sub machine
- lines 24 . 26: debounce machine

 ### Utilities

 - lines 28 - 45: Display functions
    - lines 29 - 33: show red led only
    - lines 35 - 39: show yellow led only
    - lines 41 - 45: show green led only
- line 47: boolean oneShot variable for signalling

### Arduino framework functions

- lines 49 - 55: setup, setting pin directions
- lines 57 - 60: loop, running main machine and debounce machine

### State machine stance implementations

- lines 62 - 83: debounce machine
    - lines 63 - 66: stableLow
    - lines 68 - 71: transient high
    - lines 73 - 77: stable high
    - lines 79 - 83: transient high
- lines 85 - 99: main machine
    - lines 86 - 89: forth
    - lines 91 - 94: back
    - lines 96 - 99: backAndForth
- lines 101 - 111: sub machine stances
    - lines 102 - 104: forth sub machine
    - lines 105 - 107: back sub machine
    - lines 108 - 111: back and forth sub machine

