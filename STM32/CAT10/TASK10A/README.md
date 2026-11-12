# CAT10 / TASK10A — STM32–Wemos UART bridge

## Original project reused
`PROJECT_DOCUMENTATION/Reference/EX3/wifi/` supplies the STM32F103C8 CubeMX/Keil project, USART1/USART2 setup and full-duplex terminal bridge. Its original project files remain preserved there; the task folder contains the integrated project configuration and source. `Drivers/` links to that project's matching STM32F1 HAL and CMSIS files.

## Behavior and wiring
USART1 (PA9 TX, PA10 RX) connects to the Wemos D1 Mini/ESP8266. USART2 (PA2 TX, PA3 RX) connects to the PC serial terminal. The firmware forwards terminal bytes to the Wemos and Wemos replies back to the terminal. Use 115200 8-N-1, cross TX/RX, share ground, and use 3.3 V UART logic.

## Verification limits
No new build or physical UART/Wemos test is claimed. Match the terminal/modem baud and verify board pin access before flashing.
