# CAT 8 – STM32 GPIO Bring-Up and Switch-Controlled LED

## EXP
CAT 8

## DATE
18/09/2026 (Week 7)

## NAME OF EXP
STM32 GPIO Bring-Up and Switch-Controlled LED

## HARDWARE SETUP / PLATFORM
- STM32F103C8T6 Development Board
- Push Button
- LED
- STM32CubeMX
- Keil MDK / STM32CubeIDE
- STM32 HAL Libraries
- Embedded C

## TASK NO

### Task 8A – GPIO Input/Output

Interface a push-button and LED with the STM32. Configure the corresponding GPIO pins and develop firmware so that the LED follows the switch state.

### Task 8B – Event-Based Control

Modify the firmware so that each valid switch press toggles the LED state. Investigate switch bounce and implement a simple software solution to ensure one press produces one toggle.

### Task 8C – Short Press vs Long Press

Classify a button press according to its duration.

- Short press: Less than 1 second.
- Long press: Greater than or equal to 1 second.

| User Action | System Response |
|---|---|
| Short press | Toggle LED |
| Long press | LED enters continuous blinking mode |
| Next press | Stop blinking |
| Long press again | Return to blinking mode |



## CORE LOGIC / PSEUDOCODE / CODE BASE

### Pin Configuration

| Component | STM32 Pin | Configuration |
|---|---|---|
| Push Button | PA0 | Input with Pull-Up |
| LED – Code 1 | PA9 | Output Push-Pull |
| LED – Code 2 | PC13 | Output Push-Pull |

### Code 1 – GPIO Input/Output

**Source file:** `code1.c`

1. Initialize the STM32 and configure GPIO pins.
2. Read the push-button state using `HAL_GPIO_ReadPin()`.
3. If PA0 is RESET (button pressed), set PA9 HIGH.
4. Otherwise, set PA9 LOW.
5. Repeat continuously.

### Code 2 – Short Press and Long Press

**Source file:** `code2.c`

1. Read the push-button state on PA0.
2. Record the start time using `HAL_GetTick()`.
3. Wait for the button to be released.
4. Record the end time.
5. Calculate the press duration.
6. If duration is less than 1000 ms, toggle PC13 once using `HAL_GPIO_TogglePin()`.
7. If duration is greater than or equal to 1000 ms, toggle PC13 at 500 ms intervals while the button remains released.
8. Stop blinking when the button is pressed again.

### Core HAL Functions

| HAL Function | Purpose |
|---|---|
| `HAL_GPIO_ReadPin()` | Read push-button state |
| `HAL_GPIO_WritePin()` | Set LED output HIGH or LOW |
| `HAL_GPIO_TogglePin()` | Toggle LED state |
| `HAL_GetTick()` | Obtain millisecond time |
| `HAL_Delay()` | Generate delay |

## INFERENCE

The experiment demonstrates GPIO input and output interfacing using the STM32F103C8T6. It implements push-button-controlled LED operation and uses `HAL_GetTick()` to measure button press duration and distinguish short and long presses.
