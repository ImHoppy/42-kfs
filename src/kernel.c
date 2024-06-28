#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "vga.h"

/* Entry point */
void kmain()
{
	vga_clear_screen();
	uint16_t line = 0;

	vga_display("42", line, 0);
};
