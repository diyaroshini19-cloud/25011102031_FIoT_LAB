# Week 5 — LED fade with software PWM

## Objective and platform
Fade an AT89S52 LED using a Timer 0 interrupt and software PWM. The supplied category notes specify P2.0 for the PWM LED and an 11.0592 MHz crystal.

## Implementation
Timer 0 mode 1 reloads FFA4h for approximately 100 microseconds. A 20-step PWM frame gives about 500 Hz; the foreground ramp changes duty from 0 to 100% and back. The timer ISR owns the PWM counter/output.

## Build and status
Open `TASK5B.1.uvproj` in Keil or run `sdcc -mmcs51 --model-small --out-fmt-ihx TASK5B.1.c -o Objects/TASK5B.1.ihx`. SDCC 4.6.0 produced the included genuine HEX. Brightness and PWM frequency still need oscilloscope/LED hardware verification.
