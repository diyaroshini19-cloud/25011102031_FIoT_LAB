# 8051 Timer-Based LED Brightness Control

## Aim
Demonstrate software PWM by gradually changing an LED's duty cycle with an AT89S52 timer interrupt.

## Hardware and Components
- AT89S52 microcontroller board with 11.0592 MHz clock
- LED and current-limiting resistor

## Concepts Used
- Timer 0 interrupt
- Software pulse-width modulation
- Duty-cycle ramping

## Pin Connections / Wiring
| Component | Microcontroller pin | Purpose |
|---|---|---|
| LED | P2.0 | Software-PWM output |

## Working / Implementation
Timer 0 generates approximately 100 μs ticks. The interrupt advances a 20-step PWM frame and sets the output while the frame position is below the selected duty value. The main loop ramps the duty value up and down.

## Expected Output
The LED connected to P2.0 gradually brightens and dims.
