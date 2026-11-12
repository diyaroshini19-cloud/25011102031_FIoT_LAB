# Week 12 — Short and long user-button presses

## Objective and hardware
NUCLEO-F401RE B1 on PC13 (active high) controls LD2 on PA5 (active high), following ST's [UM1724 user manual](https://www.st.com/resource/en/user_manual/dm00105823.pdf). A short press toggles the LED; a press held for at least one second enters continuous blinking; a later short press stops blinking.

## Implementation
The main loop debounces the initial press, measures duration with HAL_GetTick, treats the long-press threshold once per hold, and updates blink timing without a blocking delay.

## Build and status
Open `MDK-ARM/TASK12C.uvprojx` in Keil MDK. The F401RE HAL/CMSIS tree is shared from CAT13 TASK13. ARM GCC build passed. ELF and Intel HEX are in `Build-GCC/`; short/long press timing still needs NUCLEO-F401RE testing. Rebuild with `python3 build_stm32_gcc.py STM32/CAT12/TASK12C`.
