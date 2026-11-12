# Week 7 — Dynamic LCD display

## Objective and hardware
Update cursor locations and changing numeric values on an HD44780-compatible 16×2 display using an AT89S52 4-bit GPIO interface. Verified category wiring: RS=P3.3, EN=P3.2, D4–D7=P3.4–P3.7.

## Implementation
Driver includes nibble transfers, 4-bit/2-line initialization, `lcd_goto`, `lcd_puts` and decimal number output. The main loop updates a seconds count on row 2.

## Build and test
Open `TASK7B.uvproj` in Keil or use `sdcc -mmcs51 --model-small --out-fmt-ihx TASK7B.c -o Objects/TASK7B.ihx`. The included HEX was built with SDCC 4.6.0. Display timing and contrast require hardware verification.
