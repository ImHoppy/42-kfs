#ifndef UART_H
#define UART_H

#include <stdint.h>

#include <stdarg.h>
#include <stdint.h>
#include "../io.h"

void serial_putc(char c);
void serial_puts(const char *s);

#endif
