# STM32F401RE BME280 MQTT Publishing

## Aim
Read temperature, pressure, and humidity from a BME280 and publish the readings through an ESP8266 MQTT connection.

## Hardware and Components
- STM32F401RE development board
- BME280 I²C sensor module
- ESP8266 Wi-Fi module
- Wi-Fi access point and MQTT broker

## Concepts Used
- I²C sensor communication and Bosch BME280 API
- Sensor oversampling and compensated measurements
- UART communication with ESP8266
- MQTT connection and topic publishing

## Pin Connections / Wiring
| Component signal | STM32 pin | Purpose |
|---|---|---|
| BME280 SCL / SDA | PB6 / PB7 (I2C1) | Sensor clock and data |
| ESP8266 RX / TX | PA9 / PA10 (USART1 TX/RX) | AT and MQTT modem link |
| Ground | Common GND | Shared signal reference |

The project configures I²C1 at 100 kHz and USART1 at 115200 baud. Use a compatible sensor supply and the pull-ups required by the BME280 module. Wi-Fi values in the source are placeholders to configure for the local network.

## Working / Implementation
The firmware initializes the Bosch sensor API with the primary BME280 address, 1× oversampling for temperature, pressure, and humidity, and normal mode. It connects the ESP8266 to the configured Wi-Fi network, opens TCP to `broker.emqx.io:1883`, establishes an MQTT client session, and publishes a text message containing the three sensor readings to `stm32/diya` approximately once per second.

## Expected Output
An MQTT subscriber to `stm32/diya` receives periodic messages containing temperature in °C, pressure in hPa, and relative humidity in percent.
