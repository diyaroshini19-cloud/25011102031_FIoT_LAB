# CAT7 Task 7C — 4×4 keypad controls a 16×2 LCD character

## Requirements from the CAT7 manual

Use the existing 4-bit HD44780 LCD interface and a 4×4 keypad. Move a displayed character with 2=up, 8=down, 4=left, and 6=right. The supplied manual and CAT7 circuit document the LCD but do not specify keypad row/column wiring or a connector pinout.

## Implementation and wiring defaults

The LCD driver and initialization are reused from the existing TASK7A/TASK7B implementation: RS=P3.3, EN=P3.2, D4–D7=P3.4–P3.7, RW grounded. The display is initialized for 4-bit, two-line, 5×8 mode.

This implementation assigns keypad rows to P1.0–P1.3 and columns to P1.4–P1.7, active low, with the standard matrix:

```text
1  2  3  A
4  5  6  B
7  8  9  C
*  0  #  D
```

The character starts at row 0, column 0; movement is bounded to the 2×16 display. A 20 ms debounce and release wait prevent repeated movement from one press. The keypad mapping is an implementation default because the CAT7 manual does not define it. Rewire or adjust `keypad_scan()` if the lab board uses different row/column pins.

## Project files and build

- `TASK7C.c` — LCD driver, matrix scan, debounce and cursor movement.
- `STARTUP.A51` — startup copied from the existing CAT7 Task 7B project.
- `TASK7C.uvproj` — Keil uVision project for AT89S52, 11.0592 MHz; output directory is `Objects/`.

Open `TASK7C.uvproj` in Keil uVision, select the TASK7C target, then use **Project → Build Target**. Keil writes the HEX file to `Objects/TASK7C.hex`. Verify keypad polarity and wiring on the target board before running the exercise.

The `Objects/TASK7C.hex` currently included was compiled from this source using SDCC. The Keil project has not been built with Keil in this environment.
