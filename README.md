# Foundations of IoT Laboratory

This repository contains the practical experiments performed as part of the **Foundations of IoT (FIoT) Laboratory**. The experiments cover microcontroller programming, peripheral interfacing, communication protocols, wireless connectivity and sensor-based IoT applications using 8051 and STM32 microcontrollers.

## Repository Structure

```text
25011102031_FIoT_LAB/
│
├── 8051/
│   ├── CAT2/
│   ├── CAT3/
│   ├── CAT4/
│   ├── CAT5/
│   ├── CAT6/
│   └── CAT7/
│
├── STM32/
│   ├── CAT8/
│   ├── CAT9/
│   ├── CAT10/
│   ├── CAT11/
│   ├── CAT12/
│   ├── CAT13/
│   └── CAT14/
│
├── PROJECT_DOCUMENTATION/
│   ├── Reports/
│   ├── Reference/
│   ├── Tools/
│   └── MASTER_TASK_MAPPING.md
│
└── README.md
```

Each CAT folder contains the corresponding experiment files, source code and project configurations. Individual task folders include their own README files and supporting files.

## 8051 Experiments

The 8051 experiments introduce embedded C programming and interfacing of basic peripherals with the AT89S52 microcontroller.

| Folder | Experiments |
|---|---|
| CAT2 | GPIO interfacing and LED control |
| CAT3 | Switch interfacing and polling |
| CAT4 | Matrix keypad and seven-segment display interfacing |
| CAT5 | Hardware timers, PWM generation and stepper motor interfacing |
| CAT6 | UART communication and serial debugging |
| CAT7 | LCD interfacing and display control |

These experiments provide practical experience with digital input/output, timing, interrupts, serial communication and peripheral control.

## STM32 Experiments

The STM32 experiments explore ARM Cortex-M microcontrollers and their use in IoT applications. The projects use STM32 peripherals, communication interfaces and external modules.

| Folder | Experiments |
|---|---|
| CAT8 | GPIO programming, LED and switch interfacing |
| CAT9 | UART communication and UART-controlled LED |
| CAT10 | ESP8266 Wi-Fi module interfacing and debug communication |
| CAT11 | ESP8266-based HTTP server implementation |
| CAT12 | STM32F401RE GPIO and user-input programming |
| CAT13 | Sensor-interfacing experiment |
| CAT14 | BME280 sensor interfacing, MQTT communication and Node-RED visualization |

The experiments demonstrate microcontroller peripheral programming, serial communication, wireless networking, sensor data acquisition and IoT data visualization.

## Development Tools

- **Keil µVision** – 8051 and STM32 project development.
- **STM32CubeMX** – STM32 peripheral configuration.
- **Embedded C** – Microcontroller programming.
- **Node-RED** – IoT data visualization.

## Purpose

The laboratory provides hands-on experience in developing embedded systems and connecting microcontrollers with sensors, communication modules and IoT platforms. It progresses from basic peripheral interfacing to network-connected sensor applications.

## Evaluation and validation

Run `python3 PROJECT_DOCUMENTATION/Tools/evaluate_repository.py` from the repository root to check the required task files and Keil project references. The `PROJECT_DOCUMENTATION/Reports/` folder contains structural and engineering validation reports, `PROJECT_DOCUMENTATION/Reference/` preserves original lab materials and project files, and `PROJECT_DOCUMENTATION/MASTER_TASK_MAPPING.md` records the corrected task mapping. To rebuild supported STM32 GPIO tasks, use `python3 PROJECT_DOCUMENTATION/Tools/build_stm32_gcc.py`.
