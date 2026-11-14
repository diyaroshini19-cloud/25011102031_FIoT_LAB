# STM32 UART Commands for LED Control

## Aim
Control the STM32F103C8 LED output by sending text commands over USART1.

## Hardware and Components
- STM32F103C8 development board
- USB-to-TTL serial interface or compatible terminal
- LED connected to the board output

## Concepts Used
- UART serial communication
- Text command parsing
- GPIO output control

## Pin Connections / Wiring
| Component / signal | STM32 pin | Purpose |
|---|---|---|
| Adapter TX | PA10 / USART1_RX | Sends commands to the MCU |
| Adapter RX | PA9 / USART1_TX | Receives command echo and status |
| LED | PA5 | Active-high output |
| Ground | GND | Shared signal reference |

The configured USART1 link uses 115200 baud, 8 data bits, no parity, and one stop bit.

## Working / Implementation
The program receives a line of text and echoes incoming characters. On carriage return it compares the line with `LED ON`, `LED OFF`, or `LED TOGGLE` (also accepting lowercase versions), updates PA5, and returns a status message. Other lines produce an invalid-command response.

## Expected Output
Valid commands set, clear, or toggle the PA5 LED, and the terminal receives a response describing the command result.
