# CAT 14 – MQTT Communication Using ESP8266

## EXP
CAT 14

## NAME OF EXP
MQTT Communication Using ESP8266 and STM32

## HARDWARE SETUP / PLATFORM
- STM32F401RE Development Board
- ESP8266 Wi-Fi Module
- USB-to-TTL / UART Interface (as applicable)
- Wi-Fi Network
- MQTT Broker – broker.emqx.io
- STM32CubeMX
- STM32CubeIDE / Keil MDK
- STM32 HAL Library
- ESP8266 Library
- Embedded C

## AIM

To establish Wi-Fi connectivity using the ESP8266 module and implement MQTT communication between the STM32 microcontroller and an MQTT broker.

## TASK NO

### Task – MQTT Topic Publishing

1. Initialize the ESP8266 module in Station Mode.
2. Connect the ESP8266 to a Wi-Fi network using the network SSID and password.
3. Establish a TCP connection with the MQTT broker.
4. Configure the MQTT client parameters.
5. Connect the MQTT client to the broker.
6. Publish data to an MQTT topic at regular one-second intervals.



## CORE LOGIC / PSEUDOCODE / CODE BASE

### UART Configuration

| Parameter | Configuration |
|---|---|
| Peripheral | USART1 |
| Baud Rate | 115200 |
| Word Length | 8 Bits |
| Stop Bits | 1 |
| Parity | None |
| Mode | TX and RX |
| Hardware Flow Control | None |

### ESP8266 Configuration

| Parameter | Configuration |
|---|---|
| Operating Mode | Station Mode |
| Wi-Fi Network | SNUC |
| MQTT Broker | broker.emqx.io |
| Protocol | TCP |
| Port | 1883 |

### MQTT Client Configuration

| Parameter | Configuration |
|---|---|
| Client ID | BluePill_MQTT_01 |
| Keep Alive | 500 |
| Session | Clean Session |
| Quality of Service | QoS 0 |
| Topic | stm32/test/data |
| Published Message | diya |
| Publishing Interval | 1000 ms |

### Core Logic

1. Initialize the HAL library.
2. Configure the system clock.
3. Initialize GPIO and USART1.
4. Initialize the ESP8266 in Station Mode using `ESP8266_Init()`.
5. Connect to the Wi-Fi network using `ESP8266_wifiConnect()`.
6. Establish a TCP connection with the MQTT broker using `ESP8266_portConnect()`.
7. Configure the MQTT client parameters.
8. Connect to the MQTT broker using `MQTT_connectBroker()`.
9. Store the initial system tick using `HAL_GetTick()`.
10. Check whether 1000 milliseconds have elapsed.
11. Publish the message `diya` to the topic `stm32/test/data` using `MQTT_publishTopic()`.
12. Repeat the publishing process continuously.

### Important Functions

| Function | Purpose |
|---|---|
| `ESP8266_Init()` | Initializes the ESP8266 in Station Mode. |
| `ESP8266_wifiConnect()` | Connects to the Wi-Fi network. |
| `ESP8266_portConnect()` | Establishes a TCP connection with the MQTT broker. |
| `MQTT_connectBroker()` | Connects the MQTT client to the broker. |
| `MQTT_publishTopic()` | Publishes data to the specified MQTT topic. |
| `HAL_GetTick()` | Retrieves the system tick count in milliseconds. |

## SOURCE CODE

`main.c`

## INFERENCE

The experiment demonstrates Wi-Fi connectivity and MQTT-based data publishing using the STM32F401RE and ESP8266. The microcontroller establishes a connection with an MQTT broker and periodically publishes messages to a specified topic at one-second intervals.
