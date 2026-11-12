# CAT10 / TASK10C — Wi-Fi station, debug and TCP server setup

## Original project reused
Uses the STM32F103C8 CubeMX/Keil project and Wi-Fi command sequence from `PROJECT_DOCUMENTATION/Reference/EX3/uarthttp/`. CAT10's documented server setup is added after association and IP/status reporting. `Drivers/` links to this original project's matching STM32F1 HAL and CMSIS files. The original reference project remains unchanged.

## Firmware sequence
The task checks `AT`, selects station mode (`AT+CWMODE=1`), enables DHCP, optionally joins the configured AP with `AT+CWJAP`, reports `AT+CIFSR`/`AT+CIPSTATUS`, enables multi-connection mode (`AT+CIPMUX=1`) and starts a TCP server on port 80 (`AT+CIPSERVER=1,80`). HTTP request parsing and response generation are in CAT11 tasks per the corrected mapping.

Set `WIFI_SSID` and `WIFI_PASSWORD` in `Core/Src/main.c` locally; placeholders are provided. USART1 PA9/PA10 connects to the Wemos; USART2 PA2/PA3 is the PC debug terminal.

## Verification limits
No network association, server connection or new build is claimed. Confirm local credentials, ESP8266 firmware/baud, and board wiring before use.
