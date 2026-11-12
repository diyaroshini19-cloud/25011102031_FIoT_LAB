#include <reg51.h>

volatile unsigned char tx_busy;

void uart_isr(void)
#ifdef __SDCC
__interrupt (4)
#else
interrupt 4
#endif
{
    if (TI) { TI = 0; tx_busy = 0; }
    if (RI) { (void)SBUF; RI = 0; }
}

void uart_init(void)
{
    SCON = 0x50;
    TMOD = (TMOD & 0x0F) | 0x20;
    TH1 = 0xFD; TL1 = 0xFD;
    TR1 = 1; ES = 1; EA = 1;
}

void uart_putc(unsigned char c)
{
    while (tx_busy) { ; }
    tx_busy = 1; SBUF = c;
}

void uart_puts(const char *s)
{
    while (*s) uart_putc((unsigned char)*s++);
}

void delay(void)
{
    unsigned int i;
    for (i = 0; i < 50000; ++i) { ; }
}

void main(void)
{
    uart_init();
    while (1) { uart_puts("Hello from 8051\r\n"); delay(); }
}
