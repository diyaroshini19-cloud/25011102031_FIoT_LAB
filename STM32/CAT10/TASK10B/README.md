# CAT10 / TASK10B — ESP8266 AT command interface

## Original project reused
Based on `reference/EX3/uartwifi/` (STM32F103C8 CubeMX/Keil configuration and UART receive-to-idle pattern). The task source adds the CAT10 command investigation sequence and retains an interactive terminal bridge. `Drivers/` links to this original project's matching STM32F1 HAL and CMSIS files. Original reference files are unchanged.

## Commands and outputs
At startup, USART1 sends `AT`, `AT+GMR`, `AT+CWMODE?`, `AT+CWLAP`, and `AT+CIFSR`; responses are shown on the USART2 debug terminal. After the initial sequence, type additional commands in the terminal.

| Command | Lab use |
|---|---|
| `AT` | Check modem response |
| `AT+GMR` | Read firmware version |
| `AT+CWMODE=1` | Set station mode |
| `AT+CWLAP` | Scan visible access points |
| `AT+CWJAP="<ssid>","<password>"` | Join a configured AP (run locally; credentials are not embedded) |
| `AT+CIFSR` | Report local IP/interface information |
| `AT+CIPSTART="TCP","<host>",<port>` | Start a TCP client connection |
| `AT+CIPSEND=<length>` | Begin sending application data after the modem prompt |

USART1 PA9/PA10 connects to the ESP8266; USART2 PA2/PA3 connects to the PC terminal. Configure both ends for 115200 8-N-1, cross TX/RX and share ground.

## Verification limits
No new build or modem response test is claimed. Scan duration and response length depend on the local RF environment and ESP8266 AT firmware.
