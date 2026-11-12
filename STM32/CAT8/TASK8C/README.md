# Week 8 — Short/long press LED control

## Objective and platform
STM32F103C6 GPIO task. A short press toggles the LED; a press held for at least one second enters continuous blinking; a later short press exits blink mode.

## Wiring and implementation
Reuses verified task8A wiring: active-low PA0 button and active-high PA9 LED. The input is debounced for 25 ms, and blink timing uses HAL ticks without blocking the press-duration state machine.

## Build and status
Open `MDK-ARM/TASK8C.uvprojx` in Keil MDK. Drivers links to the existing task8A project vendor tree. ARM GCC build passed. ELF and Intel HEX are in `Build-GCC/`; physical button timing remains unverified. Rebuild with `python3 build_stm32_gcc.py STM32/CAT8/TASK8C`.
