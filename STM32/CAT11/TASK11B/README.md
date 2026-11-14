# Node-RED HTTP Client for the ESP8266 Server

## Aim
Use Node-RED as a second HTTP client to request a page from the STM32/ESP8266 server and view its response.

## Hardware and Components
- STM32F103C8 development board
- Wemos D1 Mini/ESP8266 module
- Wi-Fi access point
- Computer running Node-RED

## Concepts Used
- HTTP client request
- TCP/IP over Wi-Fi
- HTTP response inspection in Node-RED
- ESP8266 `+IPD` server-side reception

## Pin Connections / Wiring
| Link | STM32 connection | Purpose |
|---|---|---|
| ESP8266 TX/RX | PA10 / PA9 (USART1 RX/TX) | Server network interface |
| Computer network | Wi-Fi LAN | Node-RED client connection |

The STM32 and Node-RED host must be able to reach the same ESP8266 server address. UART connections use 3.3 V logic and common ground.

## Working / Implementation
The MCU configures the ESP8266 TCP server on port 80 and handles incoming `+IPD` data with the HTTP request/response logic. In Node-RED, connect an Inject node to an HTTP Request node configured for GET at `http://<ESP8266_IP>/`, then connect the response to a Debug node.

## Expected Output
Triggering Inject causes Node-RED to display the HTTP response returned by the STM32/ESP8266 server.
