# CAT14 / TASK14 — BME280 sensor data over MQTT

## Corrected source mapping
The supplied document is printed CAT13, but its combined BME280/I²C, Bosch API, custom ESP8266 MQTT API and Node-RED experiment maps to `STM32/CAT14/TASK14`. Existing CAT14 MQTT source and project setup are retained and extended with the Bosch BME280 files reused from the prior CAT13 task copy.

## Hardware and firmware
STM32F401RE with BME280 over I²C1 (PB8 SCL, PB9 SDA; use the module's actual address, 0x76 by default). ESP8266 uses USART1 PA9/PA10 at its configured baud. The firmware initializes Bosch compensation/settings, reads temperature, pressure and humidity each second, formats JSON and publishes QoS 0 to `stm32/test/data` through `broker.emqx.io:1883`. It also subscribes to `IOT`; received MQTT bytes are processed by the preserved `ESPLib` receiver and `MQTTDataHandler`. `MQTTTimer()` is called from SysTick as required by that API.

## Local configuration and visualization
Set Wi-Fi SSID/password locally in `Core/Src/main.c`; do not commit personal credentials. Import the adjacent `node-red-flow.json` into Node-RED (install the dashboard nodes if needed), configure/use the public broker, and open the dashboard to graph temperature, pressure and humidity. The JSON payload keys are `temperature_centi_c`, `pressure_hpa`, and `humidity_centi_pct`.

## Verification limits
No hardware, broker or Node-RED session was available. No fresh build or successful sensor/network test is claimed. Check BME280 address/pull-ups and the board's I²C/UART wiring before use.
