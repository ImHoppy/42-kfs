#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>
#include <stdbool.h>

#define KEYBOARD_DATA_PORT 0x60

uint8_t keyboard_read();

#endif
