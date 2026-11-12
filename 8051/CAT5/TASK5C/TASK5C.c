#include <reg51.h>

/* Timer 0 mode 1: 922 machine cycles at 11.0592 MHz ~= 1.0004 ms. */
volatile unsigned int milliseconds;
volatile unsigned char step_due;
unsigned char step_period = 100;
unsigned char phase_index = 0;
unsigned char direction_reverse = 0;
unsigned char phases[4] = { 0x08, 0x04, 0x02, 0x01 };

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
    if (step_due < 255) ++step_due;
}

unsigned int clock_ms(void)
{
    unsigned int value;
    EA = 0;
    value = milliseconds;
    EA = 1;
    return value;
}

void main(void)
{
    unsigned char last_speed = 1, last_direction = 1;
    unsigned char speed_sample, direction_sample;
    unsigned int speed_changed = 0, direction_changed = 0;
    unsigned int now;
    unsigned char due;

    P1 = 0x00;             /* P1.0..P1.3 drive four driver inputs */
    P3 |= 0x03;            /* P3.0/P3.1 buttons, active low */
    speed_sample = last_speed = (P3 & 0x01) ? 1 : 0;
    direction_sample = last_direction = (P3 & 0x02) ? 1 : 0;

    TMOD = (TMOD & 0xF0) | 0x01;
    TH0 = 0xFC;
    TL0 = 0x66;
    milliseconds = 0;
    step_due = 0;
    ET0 = 1;
    EA = 1;
    TR0 = 1;

    while (1) {
        now = clock_ms();

        /* 20 ms sampled debounce, active-low speed button cycles 100/50/10. */
        if (((P3 & 0x01) ? 1 : 0) != speed_sample) {
            speed_sample = (P3 & 0x01) ? 1 : 0;
            speed_changed = now;
        } else if ((unsigned int)(now - speed_changed) >= 20 &&
                   speed_sample != last_speed) {
            last_speed = speed_sample;
            if (last_speed == 0) {
                if (step_period == 100) step_period = 50;
                else if (step_period == 50) step_period = 10;
                else step_period = 100;
            }
        }

        /* 20 ms sampled debounce, active-low direction button reverses. */
        if (((P3 & 0x02) ? 1 : 0) != direction_sample) {
            direction_sample = (P3 & 0x02) ? 1 : 0;
            direction_changed = now;
        } else if ((unsigned int)(now - direction_changed) >= 20 &&
                   direction_sample != last_direction) {
            last_direction = direction_sample;
            if (last_direction == 0) direction_reverse = !direction_reverse;
        }

        EA = 0;
        due = step_due;
        EA = 1;
        if (due >= step_period) {
            EA = 0;
            if (step_due >= step_period) step_due -= step_period;
            else step_due = 0;
            EA = 1;

            if (direction_reverse) {
                if (phase_index == 0) phase_index = 3;
                else --phase_index;
            } else {
                phase_index = (phase_index + 1) & 0x03;
            }
            P1 = (P1 & 0xF0) | phases[phase_index];
        }
    }
}
