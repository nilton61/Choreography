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

The trasitions between the main states are controlled by a user pushbutton switch which has its own state machine for debouncing. The debounce state machine communicates its actions via a boolean variable named oneShot, which is high exactly 1 arduino-loop cycle when pressed by the user. The state diagram is as following

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
