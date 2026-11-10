# CAT 2 – 8051 Tool Chain Setup and Development Board – AT89S52



## DATE
20/07/2026 (Week 2)

## NAME OF EXP
8051 Tool Chain Setup – Development Board – AT89S52

## HARDWARE SETUP / PLATFORM

- AT89S52 Development Board
- Debugger/Programmer
- Power Source
- User LED
- Host Computer
- Keil µVision
- Embedded C



### 1. Hardware Board Bring-Up

- Identify the microcontroller, debugger/programmer, power source, user LED, and relevant GPIO pin.
- Verify the board's power rails using a digital multimeter.
- Identify the LED GPIO port and pin from the datasheet/schematic.
- Establish communication between the host computer and the target MCU.

### 2. Bare-Metal LED Blink

- Configure the LED GPIO as an output using direct register access.
- Write a delay mechanism using a simple software loop.
- Blink the LED at approximately 1 Hz.

### 3. Customized Library Function

Develop a customized library function for delay functionality.


## CORE LOGIC / PSEUDOCODE / CODE BASE

### Source Code: cat2.c

```c
#include <reg51.h>

sbit LED = P1^0;

void delay()
{
    unsigned int i, j;

    for(i = 0; i < 500; i++)
    {
        for(j = 0; j < 1275; j++);
    }
}

void main()
{
    while(1)
    {
        LED = 1;
        delay();

        LED = 0;
        delay();
    }
}
```

### Core Logic

1. Include the `reg51.h` header file.
2. Define LED using `P1^0`.
3. Define a delay function using nested software loops.
4. Set LED to HIGH.
5. Call the delay function.
6. Set LED to LOW.
7. Call the delay function.
8. Repeat continuously using `while(1)`.


## INFERENCE

The LED was successfully blinked by toggling GPIO pin P1.0 of the AT89S52 using a software delay loop. However, the exact delay duration could not be precisely controlled using nested loops, as the execution time depends on the instruction cycles.





