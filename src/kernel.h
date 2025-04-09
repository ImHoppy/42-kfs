#ifndef KERNEL_H
#define KERNEL_H

#include <stdint.h>

#define MIN(a, b) ((a > b) ? b : a)
#define MAX(a, b) ((b > a) ? b : a)

uint16_t printf(uint8_t line, const char *format, ...);

#endif
