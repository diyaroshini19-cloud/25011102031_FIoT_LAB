#include <reg51.h>

#ifdef __SDCC
__sbit __at (0x91) LED;
#else
sbit LED = P1^1;
#endif

/* 11.0592 MHz / 12 = 921.6 kHz. 922 counts gives 1.0004 ms. */
volatile unsigned int milliseconds;

void timer0_isr(void)
#ifdef __SDCC
__interrupt (1)
#else
interrupt 1
#endif
{
    TH0 = 0xFC;
    TL0 = 0x66;
    ++milliseconds;
}

void main(void)
{
    TMOD = (TMOD & 0xF0) | 0x01; /* Timer 0, 16-bit mode */
    TH0 = 0xFC;
    TL0 = 0x66;
    milliseconds = 0;
    ET0 = 1;
    EA = 1;
    TR0 = 1;

    while (1) {
        EA = 0;
        if (milliseconds >= 1000) {
            milliseconds -= 1000;
            LED = !LED;
        }
        EA = 1;
    }
}
