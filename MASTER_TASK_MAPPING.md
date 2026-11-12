# Weekly syllabus to evaluation task mapping

The weekly syllabus is the authority for *what* each experiment covers. The exact evaluation paths listed below determine *where* files belong. Printed CAT numbers and dates in individual lab sheets are treated only as source labels.

| Syllabus week | Experiment and platform | Evaluation task folder(s) | Mapping notes |
|---|---|---|---|
| 1 | Commercial IoT product teardown | No required task path | General lab activity only; the 28-task report has no Week 1 folder. |
| 2 | GPIO interfacing, AT89S52 | `8051/CAT2/TASK2B` | LED GPIO and custom delay. The source lab sheet is titled tool-chain/board bring-up. |
| 3 | Switch polling, AT89S52 | `8051/CAT3/TASK3A` | Four LED modes advance on a debounced push-button. |
| 4 | Keypad matrix and seven-segment display, AT89S52 | `8051/CAT4/TASK4A` | Reuse the category keypad/display implementation and its documented P2/P0/P1 wiring. |
| 5 | Hardware timer, PWM, signal generation and stepper, AT89S52 | `8051/CAT5/TASK5A`, `8051/CAT5/TASK5B/TASK5B.1`, `.2`, `.3`, `8051/CAT5/TASK5C` | The supplied CAT5 lab sheet is printed as Week 4. Syllabus Week 5 governs the mapping. Timer clock is 11.0592 MHz. TASK5C has implemented/documented default driver and button pins because the manual omits them; confirm against the target board. |
| 6 | UART driver and serial debugging, AT89S52 | `8051/CAT6/TASK6A`, `8051/CAT6/TASK6B` | The supplied CAT6 sheet is printed as Week 5. It describes 9600 8-N-1, Timer 1 mode 2, transmit and receive/echo. |
| 7 | LCD driver and dynamic display, AT89S52 | `8051/CAT7/TASK7A`, `8051/CAT7/TASK7B`, `8051/CAT7/TASK7C` | The supplied CAT7 sheet is printed as Week 6. It specifies 16×2 HD44780 4-bit LCD, dynamic cursor/value updates, and a keypad-controlled cursor. TASK7C has an implemented/documented default 4×4 keypad pin map because the circuit omits keypad wiring; confirm against the target board. |
| 8 | STM32 Cortex-M3 GPIO LED and switch | `STM32/CAT8/TASK8A`, `TASK8B`, `TASK8C` | The supplied CAT8 sheet is printed as Week 7. Task behaviors are button-following, debounced edge toggle, and short/long press mode. Existing extracted project uses STM32F103C6 with PA0 input and PA9 LED. |
| 9 | STM32 Cortex-M3 UART-controlled LED | `STM32/CAT9/TASK9A`, `TASK9B` | The supplied CAT9 PDF was unreadable; retain and inspect the extracted task-specific projects rather than inferring details from the CAT heading. |
| 10 (source labels 9A–9C and 10C) | STM32–Wemos UART, ESP8266 AT commands, Wi-Fi station/debug reporting and TCP server setup | `STM32/CAT10/TASK10A`, `TASK10B`, `TASK10C` | `reference/EX3/wifi`, `uartwifi`, and `uarthttp` provide original STM32F103C8 projects reused for these tasks. `cat 10.pdf` supplies UART/AT/Wi-Fi activities; CAT10c DOCX Task 10C adds TCP server setup. The source labels are mapped by corrected instruction, not their printed task/week numbers. |
| 11 (original CAT10c Tasks 10D–10E) | ESP8266 HTTP server and Node-RED HTTP client | `STM32/CAT11/TASK11A`, `TASK11B` | Task 10D maps to 11A (+IPD request handling and HTTP response); Task 10E maps to 11B (Node-RED Inject → HTTP Request → Debug). Both reuse the original F103C8 HTTP server project in `reference/EX3/uarttt`. |
| 12 | STM32F401RE GPIO and user input | `STM32/CAT12/TASK12A`, `TASK12B`, `TASK12C` | The screenshot provides LED blink, remembered toggle, and short/long press requirements. NUCLEO-F401RE LD2=PA5 and B1=PC13 are supported by ST UM1724. Existing CAT12 root project is F103 and is not reused for this F401 task. |
| CAT13-labeled supplied evaluation (source PDF) | BME280 I²C sensing, Bosch API, ESP8266 MQTT and Node-RED | `STM32/CAT14/TASK14` | Corrected mapping overrides the printed CAT13 label. Retain the prior CAT13 project as historical source; reuse its Bosch driver in CAT14/TASK14 and combine it with the existing MQTT implementation. |
| CAT14 evaluation folder | BME280 JSON telemetry over MQTT with Node-RED visualization | `STM32/CAT14/TASK14` | This is the destination required by the correction; broker is `broker.emqx.io:1883`, publish topic `stm32/test/data`, subscribe topic `IOT`. |

## Mapping ambiguities and source limits

- CAT4 and CAT9 lab PDFs in the supplied specification bundle were unreadable. CAT9's extracted projects provide the strongest available task evidence; CAT4 category source and circuit are the available evidence.
- The new CAT10 PDF, CAT10c DOCX, CAT13-labeled PDF, and all files under `reference/EX3/` were inspected by contents. The original EX3 folder includes eight STM32 projects; the UART/Wi-Fi/HTTP projects were integrated into CAT10/CAT11 and the LED/switch projects were left in place. The CAT10c DOCX explicitly separates Tasks 10D and 10E, now implemented under CAT11. The printed CAT13 PDF content maps to CAT14 by user correction.
- The CAT5 document covers timer LED, PWM fade, variable-frequency signal and stepper topics, but does not establish the GPIO pins/control wiring for the stepper. CAT7 has no keypad wiring diagram. Both task folders document implementation defaults; physical wiring still needs confirmation on the actual boards.
- No assumptions are made that a PDF's printed CAT or week label equals its required repository location.
