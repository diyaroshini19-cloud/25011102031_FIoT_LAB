# Week 8 — Debounced switch edge toggles LED

## Objective and platform
STM32F103C6 GPIO task based on the supplied CAT8 project. A valid push-button press toggles the LED once; holding the button does not repeat toggles.

## Wiring and implementation
Reuses the existing task project pin map: PA0 active-low button with pull-up, PA9 active-high LED. A 25 ms debounce check is followed by waiting for release before accepting another press.

## Build and status
Open `MDK-ARM/TASK8B.uvprojx` in Keil MDK. HAL project files and startup assembly are included; Drivers is a relative link to the existing task8A HAL source tree to avoid duplicating vendor files. ARM GCC build passed. ELF and Intel HEX are in `Build-GCC/`; physical button testing remains unverified. Rebuild with `python3 build_stm32_gcc.py STM32/CAT8/TASK8B`.
