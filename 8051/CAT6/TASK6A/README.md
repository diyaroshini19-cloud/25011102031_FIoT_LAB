# Week 6 — UART transmit and serial debugging

## Objective and hardware
Transmit a repeating debug greeting from an AT89S52 over UART. Use a USB-to-TTL serial adapter at 9600 baud, 8 data bits, no parity, one stop bit; UART pins are silicon-defined RXD=P3.0 and TXD=P3.1. Use a common ground and suitable 5 V/3.3 V level compatibility.

## Implementation
Serial mode 1, Timer 1 mode 2, reload FDh at 11.0592 MHz. UART interrupts clear TX-complete and consume unused receive bytes; foreground transmission sends `Hello from 8051`.

## Build and testing
Open `TASK6A.uvproj` in Keil or use `sdcc -mmcs51 --model-small --out-fmt-ihx TASK6A.c -o Objects/TASK6A.ihx`. The included genuine HEX was built with SDCC 4.6.0. Verify the serial output in a terminal; hardware was not available here.
