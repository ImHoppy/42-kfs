#include "uart.h"
#define UART0 0x3F8 // COM1 port for x86

// Write a character to serial port
void serial_putc(char c)
{
	while (!(intb(UART0 + 5) & 0x20))
		; // Wait until ready
	outb(UART0, c);
}

// Write a string to serial port
void serial_puts(const char *s)
{
	while (*s)
	{
		serial_putc(*s++);
	}
}
