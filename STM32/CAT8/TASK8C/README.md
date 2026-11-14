# STM32 Short- and Long-Press LED Modes

## Aim
Use short and long presses on the STM32F103C6 to control an LED in steady and blinking modes.

## Hardware and Components
- STM32F103C6 development board
- Push-button input
- LED with suitable current limiting

## Concepts Used
- GPIO input and output
- Debouncing and press-duration measurement
- Non-blocking state control using the HAL timebase

## Pin Connections / Wiring
| Component | Microcontroller pin | Purpose |
|---|---|---|
| Push-button input | PA0 | Active-low input with pull-up |
| LED | PA9 | Active-high output |

## Working / Implementation
A debounced press starts duration measurement. Reaching one second enters blinking mode, with the output toggled every 250 ms. A short press toggles the steady LED state; a short press while blinking stops the blink mode.

## Expected Output
Short presses toggle the LED. Holding the button for at least one second starts blinking; a later short press stops the periodic toggling.
