#include <reg51.h>

sbit LED = P1^1;

 unsigned int ms = 0;
 unsigned int duty = 0;



void main(void)
{
    TMOD = 0x01;

    TH0 = 0xF8;
    TL0 = 0xCB;

    ET0 = 1;
    EA = 1;
    TR0 = 1;

    while(1)
    {

        if (TF0 == 1){
            TF0 = 0;

            TH0 = 0XF8;
            TL0 = 0XCB;

            ms++;
            
        }
        if(ms >= 200)
        {
            ms = 0;
            LED = ~LED;
        }

        
    }
}