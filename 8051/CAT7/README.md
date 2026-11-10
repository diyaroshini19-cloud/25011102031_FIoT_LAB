# CAT 7 – 16×2 LCD Driver Development and Dynamic Display Control

## EXP
CAT 7

## DATE
24/08/2026 (Week 6)

## NAME OF EXP
16×2 LCD Driver Development and Dynamic Display Control

## HARDWARE SETUP / PLATFORM
- AT89S52 Development Board
- 16×2 HD44780-compatible LCD
- Keil µVision
- Embedded C



### Task 7A – LCD Initialization and Character/String Display

Develop a 4-bit GPIO-based LCD driver.

- Configure the LCD in 4-bit, 2-line mode.
- Implement LCD initialization.
- Implement command and data functions.
- Display individual characters and strings.



## CORE LOGIC / PSEUDOCODE / CODE BASE

### Pin Configuration

| LCD Signal | AT89S52 Pin |
|---|---|
| RS | P3.3 |
| EN | P3.2 |
| D4 | P3.4 |
| D5 | P3.5 |
| D6 | P3.6 |
| D7 | P3.7 |

### Functions and Their Purpose

| Function | Purpose |
|---|---|
| `delay()` | Generates software delay. |
| `send_nibble()` | Sends a 4-bit data or command nibble to the LCD. |
| `lcd_cmd()` | Sends commands to the LCD. |
| `lcd_data()` | Sends character data to the LCD. |
| `lcd_init()` | Initializes the LCD in 4-bit, 2-line mode. |
| `main()` | Initializes the LCD and displays HELLO. |

### LCD Control Pins

- **RS:** Selects command or data mode.
- **EN:** Enable signal used to latch the data.
- **D4–D7:** Transfer 4-bit data to the LCD.

### LCD Initialization Commands

| Command | Function |
|---|---|
| `0x28` | 4-bit mode, 2-line display |
| `0x0C` | Display ON, cursor OFF |
| `0x06` | Entry mode |
| `0x01` | Clear display |

### Program Execution

1. Initialize the LCD.
2. Set the cursor position using `0x80`.
3. Send the characters H, E, L, L and O using `lcd_data()`.
4. Keep the program running.

### Source Code

`cat7.c`

## INFERENCE

The experiment demonstrates interfacing a 16×2 LCD with the AT89S52 using 4-bit GPIO communication. LCD initialization, command transmission and character display were implemented to display the text "HELLO".
