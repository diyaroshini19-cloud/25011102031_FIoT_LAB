# 8051 Keypad-Controlled LCD Character

## Aim
Use a 4×4 keypad to move a character around a 16×2 LCD using the direction keys 2, 8, 4, and 6.

## Hardware and Components
- AT89S52 microcontroller board
- 16×2 HD44780-compatible LCD
- 4×4 matrix keypad

## Concepts Used
- LCD four-bit interface and cursor addressing
- Matrix keypad scanning
- Button debounce and release detection
- Bounded row/column navigation

## Pin Connections / Wiring
| Component signal | Microcontroller pin | Purpose |
|---|---|---|
| LCD D4–D7 | P3.4–P3.7 | Four-bit data bus |
| LCD EN / RS | P3.2 / P3.3 | Enable and command/data control |
| Keypad rows | P1.0–P1.3 | Active-low row selection |
| Keypad columns | P1.4–P1.7 | Active-low key detection |

The keypad matrix pin assignment is the source implementation's default; the supplied manual does not provide a keypad connector map. LCD RW is held low for write-only operation.

## Working / Implementation
The LCD is initialized in four-bit, two-line mode and displays `X`. The scanner selects each keypad row and checks the column inputs. After a stable press, 2 moves up, 8 down, 4 left, and 6 right; movement stays within the display area.

## Expected Output
The character `X` moves one LCD position per accepted direction-key press and cannot move beyond the screen edges.
