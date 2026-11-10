# CAT 9 – UART Communication and LED Control

## EXP
CAT 9

## NAME OF EXP
UART Communication and LED Control using STM32

## HARDWARE SETUP / PLATFORM
- STM32F103C8T6 Development Board
- PC / Serial Terminal
- LED
- STM32CubeMX
- STM32CubeIDE / Keil
- STM32 HAL Library
- Embedded C

## TASK NO

### Task A – UART-Based LED Control

Configure USART1 for serial communication at 115200 baud.

Receive commands from the PC terminal and control the LED connected to PA5.

The supported commands are:

| Command | Operation |
|---|---|
| `LED ON` | Turns ON the LED |
| `LED OFF` | Turns OFF the LED |
| `LED TOGGLE` | Toggles the LED |
| `led on` | Turns ON the LED |
| `led off` | Turns OFF the LED |
| `led toggle` | Toggles the LED |

The received command is compared with the predefined strings, and the corresponding response is transmitted back to the terminal.

### Task B – UART Character Echo

Configure USART2 for serial communication at 115200 baud.

- Receive one character from the PC terminal.
- Transmit the received character back.
- When a carriage return (`\r`) is received, transmit a new line (`\r\n`).



## CORE LOGIC / PSEUDOCODE / CODE BASE

### Pin Configuration

| Peripheral | STM32 Pin | Function |
|---|---|---|
| USART1 TX | PA9 | UART Transmission |
| USART1 RX | PA10 | UART Reception |
| USART2 TX | PA2 | UART Transmission |
| USART2 RX | PA3 | UART Reception |
| LED | PA5 | GPIO Output |

### Task A – Source Code: `code1.c`

1. Initialize HAL and configure the system clock.
2. Initialize GPIO and USART1.
3. Receive one character using `HAL_UART_Receive()`.
4. Transmit the received character using `HAL_UART_Transmit()`.
5. Store the received characters in a buffer.
6. On receiving carriage return, terminate the string.
7. Compare the command using `strcmp()`.
8. Control PA5 using `HAL_GPIO_WritePin()` or `HAL_GPIO_TogglePin()`.
9. Transmit the corresponding response.
10. Reset the buffer index for the next command.

### Task B – Source Code: `code2.c`

1. Initialize HAL and configure the system clock.
2. Initialize GPIO and USART2.
3. Receive one character using `HAL_UART_Receive()`.
4. Check whether the received character is carriage return (`\r`).
5. If it is carriage return, transmit `\r\n`.
6. Otherwise, transmit the received character back to the terminal.

### UART Configuration

| Parameter | Configuration |
|---|---|
| Baud Rate | 115200 |
| Word Length | 8 Bits |
| Stop Bits | 1 |
| Parity | None |
| Mode | TX and RX |
| Hardware Flow Control | None |
| Oversampling | 16 |

## INFERENCE

The experiment demonstrates UART-based serial communication using STM32. It implements command-based LED control through USART1 and character reception and echo through USART2 using HAL UART functions.
