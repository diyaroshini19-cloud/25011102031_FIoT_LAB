# Week 12 — NUCLEO-F401RE LED bring-up

## Objective and hardware
Blink the onboard green LD2 LED at a fixed interval using the STM32F401RE and STM32 HAL. On NUCLEO-F401RE LD2 is PA5 (active high).

## Implementation
F401RE HAL project; HSI PLL is configured to 84 MHz; PA5 is configured as push-pull output; main toggles LD2 every 500 ms.

## Build and status
Open `MDK-ARM/TASK12A.uvprojx` in Keil MDK. The STM32F4 HAL/CMSIS tree is shared through a relative link to CAT13 TASK13 to avoid a second large vendor copy. ARM GCC build passed. ELF and Intel HEX are in `Build-GCC/`; physical board behavior remains unverified. Rebuild with `python3 build_stm32_gcc.py STM32/CAT12/TASK12A`.
