# Engineering validation report

Validation date: 2026-11-12 (incremental CAT5C/CAT7C update).

## Toolchain

- SDCC 4.6.0 is installed at `/opt/homebrew/bin/sdcc`; Homebrew installation was successful.
- `/usr/bin/make` and Python 3 are available.
- ARM GCC 16.2.0 and its binutils are installed. Keil `uv4`, STM32CubeIDE and STM32CubeMX were not found on PATH. Homebrew's GCC package did not include Newlib; firmware was built in freestanding mode without libc.

## 8051 compilation

13 task sources compiled successfully for the MCS-51 target using SDCC 4.6.0. Generated Intel HEX files are included in each task's `Objects/` directory and are compiler outputs:

- `8051/CAT2/TASK2B`
- `8051/CAT3/TASK3A`
- `8051/CAT4/TASK4A`
- `8051/CAT5/TASK5A`
- `8051/CAT5/TASK5B/TASK5B.1`
- `8051/CAT5/TASK5B/TASK5B.2`
- `8051/CAT5/TASK5B/TASK5B.3`
- `8051/CAT6/TASK6A`
- `8051/CAT6/TASK6B`
- `8051/CAT7/TASK7A`
- `8051/CAT7/TASK7B`
- `8051/CAT5/TASK5C`
- `8051/CAT7/TASK7C`

The earlier 11 HEX files had Intel HEX record structure, record lengths, checksums and EOF records checked. The new TASK5C and TASK7C sources also compiled successfully, and `packihx` converted their SDCC IHX outputs to HEX. Both builds emit SDCC's standard `reg51.h` deprecation/fallback warnings. A successful compiler exit and valid HEX do not prove functional timing or board behavior. The CAT5 stepper driver/control pinout and CAT7 keypad matrix pinout are not in the supplied manuals; implementation defaults are documented in the task READMEs and must be confirmed against the user's board before hardware operation.

## STM32 project validation and builds

- Every existing/new Keil project XML parsed, and each explicit project file reference resolved: 60/60 configuration checks passed after the CAT5C/CAT7C projects were added. The evaluator records these checks separately from structural scoring.
- CAT10/TASK10A–10C and CAT11/TASK11A–11B reuse their original STM32F103C8 projects. Each task's `Drivers/` symlink resolves to the matching original F1 HAL/CMSIS tree under `reference/EX3/` (`wifi`, `uartwifi`, `uarthttp`, or `uarttt`). Each Keil project retains `STM32F103C8`, and its five include directories for Core, F1 HAL, HAL Legacy, device CMSIS and CMSIS Core all exist. The projects reference 16 C source files each; all explicit project file paths resolve after the reference tree is restored.
- ARM GCC 16.2.0 syntax-only checks were attempted on the 80 C compilation units referenced by the five CAT10/CAT11 projects, using `-fsyntax-only -std=gnu11 -ffreestanding -mcpu=cortex-m3 -mthumb -DUSE_HAL_DRIVER -DSTM32F103xB` and the project include paths. 75/80 passed. The five `Core/Src/main.c` files could not be checked because this toolchain installation lacks the standard C headers (`stdio.h` and/or `string.h`; Newlib is unavailable). No source was altered for GCC compatibility and no firmware output was generated. This was not a full compile or link.
- CAT8 8B/8C and CAT12 12A/12B/12C were compiled and linked from all project-referenced C files using ARM GCC 16.2.0. The resulting ELF files have no unresolved symbols; matching Intel HEX files have valid record lengths, checksums and EOF records. Outputs are in each task's `Build-GCC/` directory.
- The repeatable build is `python3 build_stm32_gcc.py`; ST's GCC startup assembly and explicit F103C6/F401RE memory layouts are in `tools/`. CAT12 task source and configuration are for STM32F401RE, not the mismatched F103 configuration in the old CAT12 category root.
- CAT9 and CAT13 have pre-existing project/build artifacts from the extracted repository materials; they were not rebuilt in this environment. Their archive freshness and physical behavior were not independently established.
- No Keil-native AXF output was created. GCC ELF/HEX files are genuine builds; they do not replace the Keil IDE project and have not been flashed to a board.

## CAT10/CAT11 dependency restoration

The later published `main` revision removed `reference/EX3/` while leaving the five task `Drivers/` symlinks in place. The original reference files were still present in the local recovery history, so the matching reference tree was restored without substituting drivers from a different MCU family. After restoration, the repository evaluator reports 28/28 tasks and 198/198 required file checks passed, and project XML/source-reference checks report 60/60. CAT10/CAT11 remain uncompiled and unlinked; the ARM GCC syntax-only limitation above and lack of Keil must be considered. No physical hardware test was performed.

The staged whitespace audit against the post-deletion remote tree reports 806 `space before tab in indent` diagnostics in 92 restored CMSIS-DSP vendor files. These are inherited upstream formatting details; the vendored originals were left unchanged. The working-tree `git diff --check` and the changed hand-maintained documentation diff check pass.

## Hardware and environmental validation

No physical hardware testing was performed. CAT5C's selected motor driver/control wiring and CAT7C's selected keypad matrix wiring still require board-level confirmation and testing, along with STM32 button behavior and BME280 I²C, ESP8266 Wi-Fi/MQTT/HTTP and Node-RED operation. The corrected CAT10/CAT11 projects reuse the original STM32F103C8 configurations in `reference/EX3/`; they were structurally checked but not freshly compiled or run on hardware. CAT14 was structurally checked but not freshly compiled or run on hardware. The F401RE board pin references used for Week 12 remain supported by ST UM1724: B1 is on PC13 and LD2 is on PA5.
