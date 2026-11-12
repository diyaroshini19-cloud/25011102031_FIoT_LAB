# Week 6 — Interrupt-driven UART receive and echo

## Objective and hardware
Receive bytes on AT89S52 UART and echo them to a terminal at 9600 8-N-1. RXD=P3.0 and TXD=P3.1; use a compatible USB-to-TTL adapter and common ground.

## Implementation
Timer 1 mode 2 with TH1=FDh sets 9600 baud at 11.0592 MHz. The UART ISR stores received bytes in a 32-byte ring buffer and handles TX completion. Foreground code dequeues bytes and transmits the echo. If the ring is full, the newest byte is dropped.

## Build and testing
Open `TASK6B.uvproj` in Keil or run `sdcc -mmcs51 --model-small --out-fmt-ihx TASK6B.c -o Objects/TASK6B.ihx`. SDCC 4.6.0 produced the included genuine HEX. Terminal echo and buffer behavior need physical serial testing.
