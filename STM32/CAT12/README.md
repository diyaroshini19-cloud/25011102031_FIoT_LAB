# CAT12 category notes and Week 12 task mapping

The authoritative syllabus assigns **Week 12: STM32F401RE GPIO and user input** to the evaluation folders `TASK12A`, `TASK12B` and `TASK12C`. Those task-specific folders contain the F401RE HAL projects and are the evaluation-ready implementations.

## Original category-root material

The pre-existing root project (`ledddd.ioc`, `Core/`, `Drivers/`, `MDK-ARM/`) is retained as original source material. Its configuration targets STM32F103C8 and its README's PC13 LED claim does not match the NUCLEO-F401RE board. Do not use that root project as the Week 12 task project. The original files were preserved; the three task projects use the correct F401RE target.

## Week 12 hardware used by task folders

- MCU and board: STM32F401RE / NUCLEO-F401RE.
- LD2 user LED: PA5, active high.
- B1 user switch: PC13, active high; GPIO configured without an internal pull because the board provides its input network.
- Clock: HSI with PLL to 84 MHz.

The board mapping follows ST's [UM1724 NUCLEO-F401RE user manual](https://www.st.com/resource/en/user_manual/dm00105823.pdf). Task-specific objectives, implementation and builds are documented in each `TASK12*/README.md`.
