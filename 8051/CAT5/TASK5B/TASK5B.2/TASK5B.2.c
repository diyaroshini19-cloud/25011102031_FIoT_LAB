#include <reg51.h>
#ifdef __SDCC
__sbit __at (0x91) WAVE_OUT;
#else
sbit WAVE_OUT = P1^1;
#endif

/* Timer 0 tick ~= 50 us at 11.0592 MHz. Test the frequencies with a scope. */
volatile unsigned char half_period_ticks = 100;
volatile unsigned int tick_count;
volatile unsigned char mode;

void timer0_isr(void)
#ifdef __SDCC
__interrupt (1)
#else
interrupt 1
#endif
{
    TH0 = 0xFF; TL0 = 0xD2; /* 46 counts ~= 49.9 us */
    ++tick_count;
    if (tick_count >= half_period_ticks) {
        tick_count = 0;
        WAVE_OUT = !WAVE_OUT;
    }
}

void main(void)
{
    unsigned int dwell = 0;
    static const unsigned char divisors[5] = {100, 20, 10, 5, 2};
    TMOD = (TMOD & 0xF0) | 0x01;
    TH0 = 0xFF; TL0 = 0xD2;
    ET0 = 1; EA = 1; TR0 = 1;
    while (1) {
        /* Cycle 100, 500, 1000, 2000 and 5000 Hz nominal settings. */
        if (++dwell >= 40000) {
            dwell = 0;
            EA = 0;
            mode = (mode + 1) % 5;
            half_period_ticks = divisors[mode];
            tick_count = 0;
            EA = 1;
        }
    }
}
