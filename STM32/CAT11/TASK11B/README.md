# CAT11 / TASK11B — Node-RED HTTP client

## Original project reused
Implements original CAT10 Task 10E at the corrected path `STM32/CAT11/TASK11B`. It uses the same STM32F103C8 server project and `+IPD`/HTTP response firmware from `PROJECT_DOCUMENTATION/Reference/EX3/uarttt/`, preserving a standalone task project copy. `Drivers/` links to that original project's matching STM32F1 HAL and CMSIS files.

## Node-RED client procedure
1. Start the STM32 HTTP server and connect ESP8266 and Node-RED host to the same Wi-Fi LAN.
2. In Node-RED wire **Inject → HTTP Request → Debug**. Set the request method to GET and URL to `http://<ESP8266_IP>/`.
3. Deploy, trigger Inject, and inspect the response body in Debug.

The board sends an HTTP 200 response with a static HTML page. Set `WIFI_SSID`/`WIFI_PASSWORD` locally in the MCU source. USART1 PA9/PA10 is the Wemos link; USART2 PA2/PA3 is debug.

## Verification limits
The Node-RED flow was not run against a live broker/network or board; no new build or hardware result is claimed.
