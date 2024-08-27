#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "vga.h"

/* Entry point */
void kmain()
{
	vga_clear_screen();

	uint16_t index = vga_display("42", 0, 0);
	vga_set_cursor(index / VGA_WIDTH, index % VGA_WIDTH);
};
