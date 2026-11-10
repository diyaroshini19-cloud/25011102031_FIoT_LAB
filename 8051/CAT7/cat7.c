#include <reg51.h>

sbit EN = P3^2;
sbit RS = P3^3;

void delay(unsigned int t)
{
    unsigned int i, j;

    for(i = 0; i < t; i++)
        for(j = 0; j < 1275; j++);
}

void send_nibble(unsigned char n)
{
    P3 = (P3 & 0x0F) | ((n & 0x0F) << 4);

    EN = 1;
    delay(1);
    EN = 0;
}

void lcd_cmd(unsigned char cmd)
{
    RS = 0;

    send_nibble(cmd >> 4);
    send_nibble(cmd & 0x0F);

    delay(2);
}

void lcd_data(unsigned char dat)
{
    RS = 1;

    send_nibble(dat >> 4);
    send_nibble(dat & 0x0F);

    delay(1);
}

void lcd_init()
{
    delay(20);

    RS = 0;

    send_nibble(0x03);
    delay(5);

    send_nibble(0x03);
    delay(1);

    send_nibble(0x03);
    delay(1);

    send_nibble(0x02);
    delay(1);

    lcd_cmd(0x28);
    lcd_cmd(0x0C);
    lcd_cmd(0x06);
    lcd_cmd(0x01);

    delay(5);
}

void main()
{
    lcd_init();

    lcd_cmd(0x80);

    lcd_data('H');
    lcd_data('E');
    lcd_data('L');
    lcd_data('L');
    lcd_data('O');

    while(1);
}