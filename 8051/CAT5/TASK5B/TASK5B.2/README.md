# Week 5 — Variable-frequency square wave

## Objective and platform
Generate nominal 100 Hz, 500 Hz, 1 kHz, 2 kHz and 5 kHz square waves with the AT89S52 and its 11.0592 MHz clock.

## Hardware
The output uses P1.1, the verified CAT5 LED output pin. Connect a logic analyzer/oscilloscope there for measurement.

## Implementation
Timer 0 interrupt provides an approximately 49.9 microsecond tick. A divider selects the requested half-periods; firmware cycles through the five frequencies automatically because the supplied material does not specify mode-select switch wiring. The upper rates are software-interrupt limited and must be measured; these values are nominal settings, not claimed measurements.

## Build and test
Open `TASK5B.2.uvproj` in Keil or run `sdcc -mmcs51 --model-small --out-fmt-ihx TASK5B.2.c -o Objects/TASK5B.2.ihx`. The included HEX was built successfully by SDCC 4.6.0. Verify each frequency and duty cycle with a scope.
