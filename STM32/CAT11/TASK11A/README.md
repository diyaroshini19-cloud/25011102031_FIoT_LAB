# ESP8266 HTTP Server and Request Handling

## Aim
Receive HTTP requests delivered by an ESP8266 TCP server and return an HTTP response from the STM32F103C8.

## Hardware and Components
- STM32F103C8 development board
- Wemos D1 Mini/ESP8266 module
- Wi-Fi access point and HTTP client
- PC serial terminal for debug output

## Concepts Used
- UART AT-command interface
- TCP server on port 80
- ESP8266 `+IPD` data framing
- HTTP request parsing and response construction

## Pin Connections / Wiring
| Link | STM32 connection | Purpose |
|---|---|---|
| ESP8266 TX/RX | PA10 / PA9 (USART1 RX/TX) | Network data and AT commands |
| PC terminal TX/RX | PA3 / PA2 (USART2 RX/TX) | Request/debug reporting |
| Ground | Common GND | Shared signal reference |

Configure the ESP8266 for the same Wi-Fi network as the HTTP client and provide local network credentials in the firmware.

## Working / Implementation
The firmware sets station mode, joins the configured network, reports its address, and starts a TCP server on port 80. It collects incoming UART data, locates and parses `+IPD` frames, recognizes HTTP requests, sends an HTTP/1.1 200 response with a static page, and closes the client connection.

## Expected Output
A browser or HTTP client requesting the ESP8266 server receives the static HTTP response. The serial debug channel shows the received network data.
