#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "vga.h"
#include "io.h"
#include "kernel.h"
#include "libft/libft.h"
#include "keyboard.h"

/* Entry point */
void kmain()
{
	vga_clear_screen();

	uint8_t last_key = 0;
	uint8_t key = 0;

	uint8_t cursor_x = 0;
	char line[64] = {0};
	uint8_t len = 0;

	printf(0, "42\n");
	while (42)
	{
		key = keyboard_read();
		uint8_t scancode = intb(KEYBOARD_DATA_PORT);
		if (scancode & RELEASED_MASK)
		{
			last_key = 0;
		}
		else if (key > 0 && key != last_key && len < (64 - 1) && ft_isprint(key))
		{
			line[len] = key;
			len++;
			printf(VGA_HEIGHT - 1, "~bprompt> ~s%s", line);
			cursor_x++;
			vga_set_cursor(VGA_HEIGHT - 1, 8 + cursor_x);
			last_key = key;
		}
	}
}
