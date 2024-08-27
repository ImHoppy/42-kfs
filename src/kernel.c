#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "vga.h"

uint16_t printf(const char *format, ...);

/* Entry point */
void kmain()
{
	vga_clear_screen();

	uint16_t index = printf("%d", 42);
	vga_set_cursor(index / VGA_WIDTH, index % VGA_WIDTH);
};
