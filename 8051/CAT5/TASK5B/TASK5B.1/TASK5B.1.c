#include <reg51.h>

#ifdef __SDCC
__sbit __at (0xA0) PWM;
#else
sbit PWM = P2^0;
#endif

unsigned char pwm_count = 0;
unsigned char duty = 0;

void Timer0_ISR(void)
#ifdef __SDCC
__interrupt (1)
#else
interrupt 1
#endif
{
    TH0 = 0xFF;
    TL0 = 0xA4;
    pwm_count++;

    if(pwm_count >= 20)
        pwm_count = 0;

    if(pwm_count < duty)
        PWM = 1;
    else
        PWM = 0;
}

void Timer0_Init(void)
{
    TMOD &= 0xF0;
    TMOD |= 0x01;
    /* 100 us tick at 11.0592 MHz: 92 machine cycles, reload 0xFFA4. */
    TH0 = 0xFF;
    TL0 = 0xA4;

    ET0 = 1;
    EA = 1;
    TR0 = 1;
}

void delay(void)
{
    unsigned int i;
    for (i = 0; i < 25000; ++i) { ; }
}

void main(void)
{
    Timer0_Init();

    while(1)
    {
        for(duty = 0; duty <= 20; duty++)
        {
            delay();
        }

        for(duty = 20; duty > 0; duty--)
        {
            delay();
        }
    }
}
