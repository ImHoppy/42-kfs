#include "keyboard.h"
#include "io.h"

#define SHIFT_L 0x2A
#define SHIFT_R 0x36
#define CTRL 0x1D
#define ALT 0x38
#define CAPS 0x3A

#define PRESSED_MASK 0
#define RELEASED_MASK 0x80

static bool shift = false;
static bool caps = false;
static bool control = false;
static bool alt = false;

// clang-format off
static const uint8_t scancode_table[] = {
	0, 27, '1', '2', '3', '4', '5', '6', '7', '8', /* 9 */
	'9', '0', '-', '=', '\b', /* Backspace */
	'\t', /* Tab */
	'q', 'w', 'e', 'r', /* 19 */
	't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', /* Enter key */
	0, /* 29   - Control */
	'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', /* 39 */
	'\'', '`', 0, /* Left shift */
	'\\', 'z', 'x', 'c', 'v', 'b', 'n', /* 49 */
	'm', ',', '.', '/', 0, /* Right shift */
	'*',
	0, /* Alt */
	' ', /* Space bar */
	0, /* Caps lock */
	0, /* 59 - F1 key ... > */
	0, 0, 0, 0, 0, 0, 0, 0,
	0, /* < ... F10 */
	0, /* 69 - Num lock*/
	0, /* Scroll Lock */
	0, /* Home key */
	0, /* Up Arrow */
	0, /* Page Up */
	'-',
	0, /* Left Arrow */
	0,
	0, /* Right Arrow */
	'+',
	0, /* 79 - End key*/
	0, /* Down Arrow */
	0, /* Page Down */
	0, /* Insert Key */
	0, /* Delete Key */
	0, 0, 0,
	0, /* F11 Key */
	0, /* F12 Key */
	0, /* All other keys are undefined */
};

static const uint8_t scancode_table_shift[] = {
	0, 27, '!', '@', '#', '$', '%', '^', '&', '*', /* 9 */
	'(', ')', '_', '+', '\b', /* Backspace */
	'\t', /* Tab */
	'Q', 'W', 'E', 'R', /* 19 */
	'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n', /* Enter key */
	0, /* 29   - Control */
	'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', /* 39 */
	'\"', '~', 0, /* Left shift */
	'|', 'Z', 'X', 'C', 'V', 'B', 'N', /* 49 */
	'M', '<', '>', '?', 0, /* Right shift */
	'*',
	0, /* Alt */
	' ', /* Space bar */
	0, /* Caps lock */
	0, /* 59 - F1 key ... > */
	0, 0, 0, 0, 0, 0, 0, 0,
	0, /* < ... F10 */
	0, /* 69 - Num lock*/
	0, /* Scroll Lock */
	0, /* Home key */
	0, /* Up Arrow */
	0, /* Page Up */
	'-',
	0, /* Left Arrow */
	0,
	0, /* Right Arrow */
	'+',
	0, /* 79 - End key*/
	0, /* Down Arrow */
	0, /* Page Down */
	0, /* Insert Key */
	0, /* Delete Key */
	0, 0, 0,
	0, /* F11 Key */
	0, /* F12 Key */
	0, /* All other keys are undefined */
};
// clang-format on

/*
	read scancode and return the ascii key pressed
*/
uint8_t keyboard_read()
{
	uint8_t scancode = intb(KEYBOARD_DATA_PORT);

	switch (scancode)
	{
	case SHIFT_L:
	case SHIFT_R:
		shift = true;
		return 0;
	case (SHIFT_L | RELEASED_MASK):
	case (SHIFT_R | RELEASED_MASK):
		shift = false;
		return 0;
	case CTRL:
		control = true;
		return 0;
	case (CTRL | RELEASED_MASK):
		control = false;
		return 0;
	case ALT:
		alt = true;
		return 0;
	case (ALT | RELEASED_MASK):
		alt = false;
		return 0;
	case CAPS & 0x7F:
		caps = !caps;
		return 0;
	}

	if (scancode & RELEASED_MASK)
		return 0;
	if (shift)
		return scancode_table_shift[scancode];
	return scancode_table[scancode];
}
