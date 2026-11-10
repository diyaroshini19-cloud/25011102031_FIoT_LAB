# CAT 3 – Timer-Based LED Pattern Generator and Button Interrupt Controller

## EXP
CAT 3

## DATE
27/07/2026 (Week 2)

## NAME OF EXP
Timer-Based LED Pattern Generator and Button Interrupt Controller

## HARDWARE SETUP / PLATFORM
- AT89S52 Development Board
- Four LEDs
- Push-button
- Keil µVision
- Embedded C


Design and implement a register-level GPIO controller using four LEDs as digital outputs and a push-button as a digital input.

The system operates in four modes:

1. **Mode 1 – Running LED Pattern:** LEDs glow sequentially (LED1 → LED2 → LED3 → LED4).
2. **Mode 2 – Binary Counter:** Four LEDs display a binary count from 0000 to 1111 and repeat.
3. **Mode 3 – Alternating Pattern:** LEDs display alternating patterns 1010 and 0101.
4. **Mode 4 – All LED Flash:** All four LEDs turn ON and OFF alternately.

Each valid button press advances the system to the next operating mode.

## CIRCUIT DIAGRAM

![CAT3 Circuit Diagram](circuit3.png)

## CORE LOGIC / PSEUDOCODE / CODE BASE

### Pin Configuration

| Component | 8051 Pin |
|---|---|
| LED0 | P1.1 |
| LED1 | P1.2 |
| LED2 | P1.3 |
| LED3 | P1.4 |
| ROW1 | P2.3 |
| col1 | P2.7 |

### Core Logic

- Configure four LED output pins.
- Check the push-button state using `keypress()`.
- Use `delay2()` for button checking.
- Increment the operating mode using `(mode+1)%4` when a button press is detected.
- Use a switch statement to execute the corresponding LED pattern.
- Use delay functions to control the LED patterns.

### Source Code

`cat3.c`

## INFERENCE

The experiment demonstrates four LED operating modes controlled through a push-button using the AT89S52 microcontroller. It implements sequential LED operation, binary counting, alternating patterns and simultaneous LED flashing using GPIO control.
