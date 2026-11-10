#include <reg51.h>

sbit PWM = P2^0;

unsigned char pwm_count = 0;
unsigned char duty = 0;

void Timer0_ISR(void) interrupt 1
{
    pwm_count++;

    if(pwm_count >= 100)
        pwm_count = 0;

    if(pwm_count < duty)
        PWM = 1;
    else
        PWM = 0;
}

void Timer0_Init(void)
{
    TMOD &= 0xF0;
    TMOD |= 0x02;

    TH0 = 0xEC;
    TL0 = 0xEC;

    ET0 = 1;
    EA = 1;
    TR0 = 1;
}

void delay(void)
{
    unsigned long i;

    for(i = 0; i < 30000; i++);
}

void main(void)
{
    Timer0_Init();

    while(1)
    {
        for(duty = 0; duty <= 100; duty++)
        {
            delay();
        }

        for(duty = 100; duty > 0; duty--)
        {
            delay();
        }
    }
}