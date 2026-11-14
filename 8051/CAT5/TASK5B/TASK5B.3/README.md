# 8051 Timer-Generated Waveform Patterns

## Aim
Use a timer interrupt to produce several digital waveform shapes from one AT89S52 output.

## Hardware and Components
- AT89S52 microcontroller board with 11.0592 MHz clock
- Oscilloscope or suitable logic-signal observation input

## Concepts Used
- Timer 0 interrupt timing
- Software PWM
- Square waves, variable duty cycle, narrow pulses, and bursts

## Pin Connections / Wiring
| Component | Microcontroller pin | Purpose |
|---|---|---|
| Signal observation point | P1.1 | Generated waveform output |

## Working / Implementation
Timer 0 provides approximately 50 μs ticks. The interrupt advances a 20-step PWM phase and periodically selects among a square wave, changing duty cycle, narrow pulse train, and burst followed by a quiet interval.

## Expected Output
The P1.1 signal changes shape as the program steps through the four waveform patterns.
