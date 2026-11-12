# CAT11 / TASK11A — HTTP request reception and response

## Original project reused
Implements original CAT10 Task 10D under the corrected destination `STM32/CAT11/TASK11A`. It is based on the complete STM32F103C8 project in `PROJECT_DOCUMENTATION/Reference/EX3/uarttt/`, including the `+IPD` frame parser, HTTP request accumulation, response construction, `CIPSEND` prompt/length handling and connection close. `Drivers/` links to this original project's matching STM32F1 HAL and CMSIS files. The original project and build artifacts remain preserved there.

## Behavior
The server configures station mode, DHCP, optional AP association when credentials are configured, IP/status reporting, multi-connection mode and TCP port 80. Incoming ESP8266 `+IPD` data and parsed HTTP requests are reported on USART2. A GET request receives a static HTTP/1.1 200 response.

Set `WIFI_SSID` and `WIFI_PASSWORD` locally in `Core/Src/main.c`. USART1 PA9/PA10 connects to the ESP8266; USART2 PA2/PA3 provides the debug terminal. The Node-RED client exercise is in TASK11B.

## Verification limits
No build or live HTTP response is claimed. Confirm the local network, credentials, AT firmware/baud and UART wiring on hardware.
