#include "uart.h"
#define UART0 0x3F8 // COM1 port for x86

// Write a character to serial port
void serial_putc(char c)
{
	while (!(intb(UART0 + 5) & 0x20))
		; // Wait until ready
	outb(UART0, c);
}

void serial_puthex(uint8_t n)
{
	while (!(intb(UART0 + 5) & 0x20))
		; // Wait until ready
	
	char c = n >> 4;
	outb(UART0, c < 10 ? c + '0' : c - 10 + 'A');
	c = n & 0x0F;
	outb(UART0, c < 10 ? c + '0' : c - 10 + 'A');	
}

// Write a string to serial port
void serial_puts(const char *s)
{
	while (*s)
	{
		serial_putc(*s++);
	}
}
