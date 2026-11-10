# CAT 6 – UART Driver and Serial Debugging

## EXP
CAT 6

## DATE
17/08/2026 (Week 5)

## NAME OF EXP
UART Driver and Serial Debugging

## HARDWARE SETUP / PLATFORM
- AT89S52 Development Board
- USB-to-TTL Converter
- PC
- PuTTY Terminal
- Keil µVision
- Embedded C

## TASK NO

### Task A – UART Initialization and Character Transmission

Configure the 8051 UART for:
- 8-bit UART mode
- Asynchronous operation
- 9600 baud
- 1 stop bit
- No parity

Transmit a character continuously from the 8051 to a PC terminal.

### Task B – UART Echo

Receive a character typed in the PC terminal and transmit the same character back to the terminal.

## CIRCUIT DIAGRAM

![UART Circuit Diagram](circuit.png)

## CORE LOGIC / PSEUDOCODE / CODE BASE

### Pin Connections

| USB-to-TTL | AT89S52 |
|---|---|
| TXD | P3.0 (RXD) |
| RXD | P3.1 (TXD) |
| GND | GND |

### Register Configuration and Functions

| Register | Function |
|---|---|
| PCON | Power control register. SMOD controls baud rate doubling. |
| SCON | Serial control register. SM0 and SM1 select UART mode; REN enables reception. |
| TMOD | Timer mode register. Configures Timer 1 in Mode 2 (8-bit auto-reload). |
| TH1 | Stores the Timer 1 reload value used for baud rate generation. |
| TR1 | Starts Timer 1 when set to 1. |
| SBUF | Serial buffer register used to transmit and receive data. |
| TI | Transmit flag, indicates completion of transmission. |
| RI | Receive flag, indicates that a character has been received. |

### USB-to-TTL Converter

The USB-to-TTL converter acts as an interface between the PC's USB port and the 8051's TTL serial communication pins.

- Converts USB data from the PC into TTL serial signals for the 8051.
- Converts TTL serial data from the 8051 into USB data for the PC.
- Provides TXD, RXD and GND connections.

### Source Code 1 – cat60.c

1. Configure UART using SM0 and SM1.
2. Configure Timer 1 in Mode 2.
3. Load TH1 with the baud rate reload value.
4. Start Timer 1 using TR1.
5. Load character 'A' into SBUF.
6. Wait until TI becomes 1.
7. Clear TI and repeat transmission.

### Source Code 2 – cat61.c

1. Configure UART and Timer 1.
2. Enable reception using REN.
3. Wait until RI becomes 1.
4. Read the received character from SBUF.
5. Clear RI.
6. Load the received character into SBUF for transmission.
7. Wait until TI becomes 1 and clear TI.

## INFERENCE

The experiment demonstrates UART character transmission and reception using the AT89S52. The USB-to-TTL converter enables serial communication between the microcontroller and PC terminal, allowing character transmission and echo operations.
