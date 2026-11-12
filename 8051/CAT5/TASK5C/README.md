# CAT5 Task 5C — Stepper motor speed and direction

## Requirements from the CAT5 manual

AT89S52 at 11.0592 MHz. Drive a four-phase stepper using the sequence `1000 → 0100 → 0010 → 0001`; provide 100 ms/step (slow), 50 ms/step (medium), and 10 ms/step (fast). The manual does not provide a motor-driver circuit, GPIO assignment, or button/control interface.

## Implemented behavior and wiring defaults

The firmware uses a Timer 0 mode 1 interrupt reloaded with `TH0=0xFC`, `TL0=0x66` for approximately 1.0004 ms ticks. Foreground logic advances the motor without busy-wait timing loops. An active-low button on P3.0 cycles 100 → 50 → 10 ms/step; an active-low button on P3.1 reverses direction. Both are debounced for 20 ms.

For this implementation, connect P1.3, P1.2, P1.1, P1.0 to the four phase inputs in that sequence, through a ULN2003 or suitable transistor driver. The generated low-nibble pattern is `1000, 0100, 0010, 0001`. Connect each button between its P3 input and ground. Power the motor from an appropriate external supply and share ground with the 8051. Never connect motor coils directly to MCU pins. These pin/control choices are implementation defaults, not pin assignments stated by the manual; adjust the source if your board wiring differs.

## Project files and build

- `TASK5C.c` — Timer 0 step scheduler, phase sequencing and button controls.
- `STARTUP.A51` — startup copied from the existing CAT5 Task 5A project.
- `TASK5C.uvproj` — Keil uVision project for AT89S52, 11.0592 MHz; output directory is `Objects/`.

Open `TASK5C.uvproj` in Keil uVision, select the TASK5C target, then use **Project → Build Target**. Keil writes the HEX file to `Objects/TASK5C.hex`. Hardware behavior still needs to be checked with the correctly wired driver and motor.

The `Objects/TASK5C.hex` currently included was compiled from this source using SDCC. The Keil project has not been built with Keil in this environment.
