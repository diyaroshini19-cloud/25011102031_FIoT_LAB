# CAT 13 – BME280 Sensor Interfacing Using I2C

## EXP
CAT 13

## NAME OF EXP
BME280 Sensor Interfacing with STM32 Using Bosch Sensor API

## HARDWARE SETUP / PLATFORM
- STM32F401RE Development Board
- BME280 Environmental Sensor
- STM32CubeMX
- Keil MDK / STM32CubeIDE
- STM32 HAL Library
- Bosch BME280 Sensor API
- Embedded C

## AIM

To interface the BME280 sensor with the STM32 microcontroller using I2C communication and retrieve temperature, pressure and humidity measurements using the Bosch Sensor API.

## TASK NO

### Task – BME280 Sensor Configuration and Data Acquisition

1. Configure the I2C peripheral for communication with the BME280 sensor.
2. Implement the hardware abstraction functions required to interface the Bosch API with STM32.
3. Initialize the BME280 sensor using the Bosch driver.
4. Configure temperature, pressure and humidity oversampling.
5. Configure the sensor filter and operating mode.
6. Read temperature, pressure and humidity measurements.
7. Apply the Bosch compensation functions to obtain the sensor readings.
8. Repeat the measurement process at one-second intervals.



## CORE LOGIC / PSEUDOCODE / CODE BASE

### I2C Configuration

| Parameter | Configuration |
|---|---|
| Peripheral | I2C1 |
| Clock Speed | 100 kHz |
| Duty Cycle | I2C_DUTYCYCLE_2 |
| Addressing Mode | 7-bit |
| Device Address | 0x76 (Primary Address) |

### Sensor Configuration

| Parameter | Configuration |
|---|---|
| Temperature Oversampling | 1X |
| Pressure Oversampling | 1X |
| Humidity Oversampling | 1X |
| Filter | Disabled |
| Operating Mode | Normal Mode |

### Hardware Abstraction Functions

| Function | Purpose |
|---|---|
| `user_i2c_read()` | Reads sensor registers using HAL I2C memory read. |
| `user_i2c_write()` | Writes data to sensor registers using HAL I2C memory write. |
| `user_delay_us()` | Provides the delay required by the Bosch driver. |

### Core Logic

1. Initialize HAL and configure the system clock.
2. Initialize GPIO and I2C1.
3. Set the BME280 I2C device address.
4. Configure the Bosch API function pointers for read, write and delay operations.
5. Initialize the BME280 sensor using `bme280_init()`.
6. Configure temperature, pressure and humidity oversampling to 1X.
7. Disable the sensor filter.
8. Set the sensor to normal operating mode.
9. Read all sensor measurements using `bme280_get_sensor_data()`.
10. Store the compensated temperature, pressure and humidity values.
11. Convert pressure from Pa to hPa.
12. Repeat the measurement process every 1000 ms.

### Sensor Output Variables

| Variable | Measurement | Unit |
|---|---|---|
| `temperature` | Temperature | °C |
| `pressure` | Atmospheric Pressure | hPa |
| `humidity` | Relative Humidity | % |

### Important Bosch API Functions

| Function | Purpose |
|---|---|
| `bme280_init()` | Initializes the BME280 sensor. |
| `bme280_set_sensor_settings()` | Configures sensor settings. |
| `bme280_set_sensor_mode()` | Sets the operating mode. |
| `bme280_get_sensor_data()` | Retrieves compensated sensor measurements. |

## SOURCE CODE

`main.c`

## INFERENCE

The experiment demonstrates I2C communication between the STM32F401RE and BME280 sensor using the Bosch Sensor API. Temperature, pressure and humidity measurements are retrieved and compensated by the driver at one-second intervals.
