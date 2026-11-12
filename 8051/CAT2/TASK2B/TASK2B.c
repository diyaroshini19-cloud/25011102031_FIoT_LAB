
#ifdef __SDCC
#include <8052.h>
#else
#include <reg52.h>
#endif

#ifdef __SDCC
__sbit __at (0x90) LED;
#else
sbit LED = P1^0;
#endif

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
