#include <reg51.h>
#ifdef __SDCC
__sbit __at (0xB2) EN;
__sbit __at (0xB3) RS;
#else
sbit EN = P3^2;
sbit RS = P3^3;
#endif

void delay_ms(unsigned int ms)
{
    unsigned int i, j;
    for (i = 0; i < ms; ++i) for (j = 0; j < 110; ++j) { ; }
}

void lcd_nibble(unsigned char value)
{
    P3 = (P3 & 0x0F) | ((value & 0x0F) << 4);
    EN = 1; EN = 0;
}

void lcd_cmd(unsigned char command)
{
    RS = 0; lcd_nibble(command >> 4); lcd_nibble(command); delay_ms(2);
}

void lcd_data(unsigned char value)
{
    RS = 1; lcd_nibble(value >> 4); lcd_nibble(value); delay_ms(1);
}

void lcd_goto(unsigned char row, unsigned char column)
{
    lcd_cmd((row ? 0xC0 : 0x80) + column);
}

void lcd_puts(const char *text)
{
    while (*text) lcd_data((unsigned char)*text++);
}

void lcd_print_number(unsigned int number)
{
    unsigned char digits[5], count = 0;
    if (number == 0) { lcd_data('0'); return; }
    while (number && count < 5) { digits[count++] = number % 10; number /= 10; }
    while (count) lcd_data((unsigned char)('0' + digits[--count]));
}

void lcd_init(void)
{
    delay_ms(20); RS = 0;
    lcd_nibble(3); delay_ms(5); lcd_nibble(3); delay_ms(1);
    lcd_nibble(3); lcd_nibble(2);
    lcd_cmd(0x28); lcd_cmd(0x0C); lcd_cmd(0x06); lcd_cmd(0x01);
}

void main(void)
{
    unsigned int seconds = 0;
    lcd_init();
    while (1) {
        lcd_goto(0, 0); lcd_puts("Elapsed seconds ");
        lcd_goto(1, 0); lcd_puts("Count:          ");
        lcd_goto(1, 7); lcd_print_number(seconds++);
        delay_ms(1000);
    }
}
