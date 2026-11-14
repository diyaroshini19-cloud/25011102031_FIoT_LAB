# 8051 Switch-Controlled LED Patterns

## Aim
Use a push-button input to select and observe four LED patterns on an AT89S52.

## Hardware and Components
- AT89S52 microcontroller board
- Four LEDs with current-limiting resistors
- Push-button switch

## Concepts Used
- GPIO input polling
- Switch debounce by software delay
- LED sequencing and binary patterns

## Pin Connections / Wiring
| Component | Microcontroller pin | Purpose |
|---|---|---|
| LEDs 0–3 | P1.1–P1.4 | Four pattern outputs |
| Button row signal | P2.3 | Selected low during scan |
| Button column signal | P2.7 | Press detection input |

## Working / Implementation
The program polls the switch and advances a four-state mode when a press is detected. The modes run a moving LED, count a four-bit value from 0 to 15, alternate two complementary patterns, and flash all four LEDs together.

## Expected Output
Each accepted button press selects the next pattern. The four LEDs visibly show the selected sequence or value.
