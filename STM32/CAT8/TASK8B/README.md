# STM32 Debounced Button Toggle

## Aim
Toggle an LED once for each accepted push-button press on the STM32F103C6.

## Hardware and Components
- STM32F103C6 development board
- Push-button input
- LED with suitable current limiting

## Concepts Used
- GPIO input and output
- Active-low button polling
- Debounce interval and press-edge detection

## Pin Connections / Wiring
| Component | Microcontroller pin | Purpose |
|---|---|---|
| Push-button input | PA0 | Active-low input with pull-up |
| LED | PA9 | Output toggled on a press edge |

## Working / Implementation
The main loop detects a high-to-low transition on PA0, waits 25 ms, and confirms that the input remains pressed. It toggles PA9 once and waits for release before accepting another press.

## Expected Output
Each distinct button press changes the LED to the opposite state; holding the button does not repeatedly toggle it.
