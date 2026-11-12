#include <reg51.h>

#define RX_BUFFER_SIZE 32
volatile unsigned char rx_buffer[RX_BUFFER_SIZE];
volatile unsigned char rx_head, rx_tail;
volatile unsigned char tx_busy;

void uart_isr(void)
#ifdef __SDCC
__interrupt (4)
#else
interrupt 4
#endif
{
    unsigned char c;
    if (RI) {
        c = SBUF; RI = 0;
        if ((unsigned char)((rx_head + 1) % RX_BUFFER_SIZE) != rx_tail) {
            rx_buffer[rx_head] = c;
            rx_head = (unsigned char)((rx_head + 1) % RX_BUFFER_SIZE);
        }
    }
    if (TI) { TI = 0; tx_busy = 0; }
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

void main(void)
{
    uart_init();
    while (1) {
        if (rx_tail != rx_head) {
            unsigned char c = rx_buffer[rx_tail];
            rx_tail = (unsigned char)((rx_tail + 1) % RX_BUFFER_SIZE);
            uart_putc(c);
        }
    }
}
