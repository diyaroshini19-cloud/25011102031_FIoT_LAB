# Foundations of IoT Lab Repository

This repository contains lab experiments for 8051 (AT89S52) and STM32 microcontrollers. It includes embedded C sources, Keil uVision projects, STM32CubeMX configurations, startup and driver files, circuit references, and task-specific instructions.

## Repository layout

- `8051/CATn/TASK.../` contains the 8051 task projects. CAT5 has TASK5A, TASK5B.1–5B.3 and TASK5C; CAT7 has TASK7A–TASK7C.
- `STM32/CATn/TASK.../` contains STM32 task projects, including CubeMX `.ioc` files, `Core/`, vendor `Drivers/`, and Keil projects in `MDK-ARM/`.
- `reference/` preserves supplied lab documents and original STM32 project materials used to map and integrate tasks.
- `tools/` contains the GCC startup and memory-layout support used by the repeatable STM32 GCC build script.
- `MASTER_TASK_MAPPING.md` records the syllabus-to-repository mapping, including the corrected CAT10/CAT11/CAT14 assignments.

Each task folder's `README.md` describes its experiment, wiring assumptions, project files, and build or validation status. Read the task instructions before connecting hardware, especially where a manual does not specify a pinout.

## Toolchains

- **8051:** Keil µVision with the C51 toolchain. The repository also contains SDCC-built MCS-51 HEX outputs for all 13 listed 8051 tasks.
- **STM32:** Keil µVision and STM32CubeMX for the provided projects. `python3 build_stm32_gcc.py` builds the verified GCC-compatible subset when ARM GCC and binutils are installed.
- **Structural checks:** run `python3 evaluate_repository.py` from the repository root. This checks required task artifacts and parses Keil XML/source references; it is not a substitute for compiling every project or testing hardware.

## Validation status

The latest structural evaluation reports **28/28 tasks**, **198/198 required-file checks**, and **60/60 Keil project XML/source-reference checks** passed. See `EVALUATION_REPORT.md` for the complete output and `ENGINEERING_VALIDATION_REPORT.md` for compiler evidence and limitations.

8051 outputs were compiled with SDCC. The STM32 tasks freshly compiled and linked with ARM GCC were CAT8B, CAT8C, CAT12A, CAT12B and CAT12C; other STM32 task compilation is not claimed here. Keil-native compilation has not been reported, and no physical hardware testing was performed. Confirm hardware wiring and credentials/placeholders against your setup before use.
