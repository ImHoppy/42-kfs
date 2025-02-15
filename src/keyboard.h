#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>
#include <stdbool.h>

#define KEYBOARD_DATA_PORT 0x60

#define SHIFT_L 0x2A
#define SHIFT_R 0x36
#define CTRL 0x1D
#define ALT 0x38
#define CAPS 0x3A

#define PRESSED_MASK 0
#define RELEASED_MASK 0x80

uint8_t keyboard_read();

#endif
