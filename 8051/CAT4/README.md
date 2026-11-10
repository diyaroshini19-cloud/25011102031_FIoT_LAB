# CAT 4 – Keypad Interfacing with 7-Segment Display and LED Control

## EXP
CAT 4

## NAME OF EXP
Keypad Interfacing with 7-Segment Display and LED Control

## HARDWARE SETUP / PLATFORM
- AT89S52 Development Board
- 7-Segment Display
- Matrix Keypad
- Four LEDs
- Keil µVision
- Embedded C

## TASK 

Interface a matrix keypad, 7-segment display and four LEDs with the AT89S52 microcontroller.

The program performs keypad scanning, displays the pressed digit on the 7-segment display and controls the LEDs based on the key pressed.

### LED Operating Modes

1. Individual LED control.
2. Running LED pattern.
3. Alternating LED pattern.
4. Binary counter (0–15).
5. All LED blinking.
6. LED OFF control.



## CORE LOGIC / PSEUDOCODE / CODE BASE

### Pin Configuration

| Component | AT89S52 Pin |
|---|---|
| Keypad columns | P2.0–P2.3 |
| Keypad rows | P2.5–P2.7 |
| LED 1 | P1.0 |
| LED 2 | P1.1 |
| LED 3 | P1.2 |
| LED 4 | P1.3 |
| 7-Segment display | P0.0–P0.7 |

### Core Logic

1. Initialize the keypad, LED and 7-segment display pin definitions.
2. Scan the keypad row by row.
3. Identify the pressed key by checking the corresponding column.
4. Apply a small delay for key confirmation.
5. Store the detected key in the `key` variable.
6. Display the corresponding digit on the 7-segment display using `display_digit()`.
7. Execute the corresponding LED operation using `led_control()`.

### Functions and Their Purpose

| Function | Purpose |
|---|---|
| `delaysmall()` | Generates a small software delay. |
| `intr()` | Checks keypad scanning status. |
| `delay()` | Generates delay while checking for keypad input. |
| `keypad_scan()` | Scans the keypad and identifies the pressed key. |
| `running_led()` | Controls sequential LED operation. |
| `alternate_led()` | Generates alternating LED patterns. |
| `binary_counter()` | Displays binary counting using four LEDs. |
| `blink_all()` | Controls all four LEDs together. |
| `display_digit()` | Displays the detected digit on the 7-segment display. |
| `led_control()` | Selects LED operation based on the pressed key. |

## SOURCE CODE

`cat4.c`

## INFERENCE

The experiment demonstrates keypad interfacing with the AT89S52, where detected key presses are displayed on a 7-segment display and used to control different LED patterns through GPIO operations.
