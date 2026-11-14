# STM32F401RE BME280 MQTT Telemetry

## Aim
Measure environmental conditions with a BME280 and publish JSON sensor data through an ESP8266 MQTT connection for Node-RED visualization.

## Hardware and Components
- STM32F401RE development board
- BME280 I²C sensor
- ESP8266 module
- Wi-Fi network and MQTT client/Node-RED dashboard

## Concepts Used
- I²C sensor interfacing and Bosch compensation API
- UART control of ESP8266
- MQTT publish/subscribe
- JSON telemetry

## Pin Connections / Wiring
| Component signal | STM32 pin | Purpose |
|---|---|---|
| BME280 SCL / SDA | PB6 / PB7 (I2C1) | Sensor bus |
| ESP8266 RX / TX | PA9 / PA10 (USART1 TX/RX) | Modem UART |
| Ground | Common GND | Shared signal reference |

The firmware uses the BME280 primary I²C address (0x76), 100 kHz I²C, and USART1 at 115200 baud. Configure Wi-Fi credentials locally.

## Working / Implementation
The Bosch API configures 1× temperature, pressure, and humidity oversampling and normal mode. Once per second the MCU reads compensated values, formats `temperature_centi_c`, `pressure_hpa`, and `humidity_centi_pct` as JSON, and publishes to `stm32/test/data` at `broker.emqx.io:1883`. The ESP library also subscribes to `IOT` and handles incoming MQTT data. The accompanying Node-RED flow uses the published sensor fields for visualization.

## Expected Output
An MQTT subscriber receives periodic JSON telemetry from the BME280, and the Node-RED flow can present the temperature, pressure, and humidity values.
