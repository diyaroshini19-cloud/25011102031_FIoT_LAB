# 8051 UART Character Echo

## Aim
Receive serial characters on the AT89S52 and return each character to the sender.

## Hardware and Components
- AT89S52 microcontroller board with 11.0592 MHz clock
- USB-to-TTL serial interface or compatible serial terminal

## Concepts Used
- UART transmit and receive
- Timer 1 mode 2 baud generation
- Serial interrupt and receive buffer

## Pin Connections / Wiring
| Component | Microcontroller pin | Purpose |
|---|---|---|
| Serial adapter TX | P3.0 / RXD | Sends characters to the MCU |
| Serial adapter RX | P3.1 / TXD | Receives echoed characters |
| Ground | GND | Shared signal reference |

Configure the serial link for 9600 baud, 8 data bits, no parity, and one stop bit.

## Working / Implementation
Timer 1 mode 2 sets the UART baud rate. The serial interrupt places received bytes into a small circular buffer and clears transmit completion flags. The main loop removes buffered bytes and sends them back through the UART.

## Expected Output
Characters typed in the terminal are returned by the board as an echo.
