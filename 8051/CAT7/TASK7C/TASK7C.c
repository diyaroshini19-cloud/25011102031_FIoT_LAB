#include <reg51.h>
#ifdef __SDCC
__sbit __at (0xB2) LCD_EN;
__sbit __at (0xB3) LCD_RS;
#else
sbit LCD_EN = P3^2;
sbit LCD_RS = P3^3;
#endif

/* LCD driver adapted from the existing TASK7A/TASK7B 4-bit implementation. */
void delay_ms(unsigned int ms)
{
    unsigned int i, j;
    for (i = 0; i < ms; ++i)
        for (j = 0; j < 110; ++j) { ; }
}

void lcd_nibble(unsigned char value)
{
    P3 = (P3 & 0x0F) | ((value & 0x0F) << 4);
    LCD_EN = 1;
    LCD_EN = 0;
}

void lcd_cmd(unsigned char command)
{
    LCD_RS = 0;
    lcd_nibble(command >> 4);
    lcd_nibble(command);
    delay_ms(2);
}

void lcd_data(unsigned char value)
{
    LCD_RS = 1;
    lcd_nibble(value >> 4);
    lcd_nibble(value);
    delay_ms(1);
}

void lcd_goto(unsigned char row, unsigned char column)
{
    lcd_cmd((row ? 0xC0 : 0x80) + column);
}

void lcd_init(void)
{
    delay_ms(20);
    LCD_RS = 0;
    lcd_nibble(3); delay_ms(5);
    lcd_nibble(3); delay_ms(1);
    lcd_nibble(3);
    lcd_nibble(2);
    lcd_cmd(0x28);         /* 4-bit, 2 lines, 5x8 font */
    lcd_cmd(0x0C);         /* display on, cursor off */
    lcd_cmd(0x06);         /* increment address */
    lcd_cmd(0x01);         /* clear display */
}

/* Default keypad wiring (not specified in supplied CAT7 manual):
   rows P1.0..P1.3, columns P1.4..P1.7, all active low. */
unsigned char keypad_scan(void)
{
    unsigned char row, col, value;
    unsigned char keys[4][4] = {
        {'1','2','3','A'}, {'4','5','6','B'},
        {'7','8','9','C'}, {'*','0','#','D'}
    };
    for (row = 0; row < 4; ++row) {
        P1 = (unsigned char)(0xFF & ~(1 << row));
        value = (P1 >> 4) & 0x0F;
        if (value != 0x0F) {
            for (col = 0; col < 4; ++col)
                if ((value & (1 << col)) == 0) return keys[row][col];
        }
    }
    P1 = 0xFF;
    return 0;
}

void show_character(unsigned char row, unsigned char column)
{
    lcd_cmd(0x01);
    lcd_goto(row, column);
    lcd_data('X');
}

void main(void)
{
    unsigned char key;
    unsigned char row = 0, column = 0;

    P1 = 0xFF;
    lcd_init();
    show_character(row, column);
    while (1) {
        key = keypad_scan();
        if (key != 0) {
            delay_ms(20);  /* debounce */
            if (keypad_scan() == key) {
                if (key == '2' && row > 0) --row;
                else if (key == '8' && row < 1) ++row;
                else if (key == '4' && column > 0) --column;
                else if (key == '6' && column < 15) ++column;
                show_character(row, column);
                while (keypad_scan() != 0) { ; }
                delay_ms(20);
            }
        }
    }
}
