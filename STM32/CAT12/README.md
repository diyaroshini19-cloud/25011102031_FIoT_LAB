# CAT 12 – LED Blinking using STM32F401RE

## EXP
CAT 12

## NAME OF EXP
GPIO-Based LED Blinking using STM32F401RE

## HARDWARE SETUP / PLATFORM
- STM32F401RE Development Board
- LED (GPIO output)
- STM32CubeMX
- STM32CubeIDE
- STM32 HAL Library
- Embedded C

## AIM
To configure a GPIO pin of the STM32F401RE microcontroller as an output and implement LED blinking using HAL GPIO functions and delay operations.

## TASK NO

### Task – LED Blinking using GPIO

The program configures GPIO pin PC13 as a push-pull output and continuously toggles its state with a delay of 100 milliseconds.

The LED connected to the configured GPIO output changes its state repeatedly, producing a blinking effect.


## PIN CONFIGURATION

| Signal | STM32 Pin | Configuration |
|---|---|---|
| LED Control | PC13 | GPIO Output Push-Pull |
| GPIO Clock | GPIOC | Enabled |
| Ground | GND | Common Ground |

## CORE LOGIC / PSEUDOCODE / CODE BASE

### Source Code: `main.c`

1. Initialize the HAL library using `HAL_Init()`.
2. Configure the system clock using `SystemClock_Config()`.
3. Enable the GPIOC peripheral clock.
4. Configure PC13 as a general-purpose output in push-pull mode.
5. Initialize the output pin to LOW.
6. Enter an infinite loop.
7. Toggle PC13 using `HAL_GPIO_TogglePin()`.
8. Introduce a 100 ms delay using `HAL_Delay(100)`.
9. Repeat continuously.

### Important HAL Functions

| Function | Purpose |
|---|---|
| `HAL_Init()` | Initializes the HAL library |
| `SystemClock_Config()` | Configures the system clock |
| `__HAL_RCC_GPIOC_CLK_ENABLE()` | Enables GPIOC peripheral clock |
| `HAL_GPIO_Init()` | Configures the GPIO pin |
| `HAL_GPIO_TogglePin()` | Toggles the output state |
| `HAL_Delay(100)` | Creates a 100 ms delay |

## INFERENCE

The experiment demonstrates GPIO configuration and digital output control using the STM32F401RE microcontroller. The LED blinking operation is achieved by repeatedly toggling GPIO pin PC13 with a 100 ms delay using STM32 HAL functions.
