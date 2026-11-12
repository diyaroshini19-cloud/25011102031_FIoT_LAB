# Week 12 — User switch with remembered LED state

## Objective and hardware
Use the NUCLEO-F401RE B1 user button to toggle and retain LD2 state after button release. ST's [UM1724 user manual](https://www.st.com/resource/en/user_manual/dm00105823.pdf) identifies B1 on PC13 and LD2 on PA5.

## Implementation
PC13 is sampled as an active-high input with no internal pull because the board provides an external pull-up. A debounced press edge toggles PA5 once, then waits for release.

## Build and status
Open `MDK-ARM/TASK12B.uvprojx` in Keil MDK. The F401RE HAL/CMSIS tree is linked from CAT13 TASK13. ARM GCC build passed. ELF and Intel HEX are in `Build-GCC/`; the button behavior still needs NUCLEO-F401RE testing. Rebuild with `python3 build_stm32_gcc.py STM32/CAT12/TASK12B`.
