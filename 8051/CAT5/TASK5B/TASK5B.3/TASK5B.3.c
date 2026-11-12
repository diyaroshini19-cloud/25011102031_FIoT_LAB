#include <reg51.h>
#ifdef __SDCC
__sbit __at (0x91) WAVE_OUT;
#else
sbit WAVE_OUT = P1^1;
#endif

volatile unsigned char phase;
volatile unsigned char pwm_step, duty = 1, ramp_up = 1;
volatile unsigned char duty_frames;
volatile unsigned int pattern_tick;

void timer0_isr(void)
#ifdef __SDCC
__interrupt (1)
#else
interrupt 1
#endif
{
    TH0 = 0xFF; TL0 = 0xD2; /* approximately 50 us */
    ++pattern_tick;
    /* Four repeating patterns, each 500 ms: square, variable duty,
       short pulse train, then ten-cycle burst followed by a quiet interval. */
    if (++pwm_step >= 20) {
        pwm_step = 0;
        if (++duty_frames >= 25) {
            duty_frames = 0;
            if (ramp_up && duty < 19) ++duty; else ramp_up = 0;
            if (!ramp_up && duty > 1) --duty; else ramp_up = 1;
        }
    }
    if (phase == 0) WAVE_OUT = pwm_step < 10;                 /* square */
    else if (phase == 1) WAVE_OUT = pwm_step < duty;         /* variable duty */
    else if (phase == 2) WAVE_OUT = pwm_step == 0;            /* narrow pulse train */
    else WAVE_OUT = pattern_tick < 200 && pwm_step < 10;      /* burst, then silence */
    if (pattern_tick >= 20000) { pattern_tick = 0; phase = (phase + 1) & 0x03; }
}

void main(void)
{
    TMOD = (TMOD & 0xF0) | 0x01;
    TH0 = 0xFF; TL0 = 0xD2;
    ET0 = 1; EA = 1; TR0 = 1;
    while (1) { ; }
}
