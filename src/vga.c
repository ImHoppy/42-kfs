#include "vga.h"

void vga_clear_screen()
{
	char *vidmem = (char *)VGA_MEMORY;
	uint16_t i = 0;
	while (i < (80 * 25 * 2))
	{
		vidmem[i] = ' ';
		i++;
		vidmem[i] = VGA_COLOR(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
		i++;
	};
};

uint16_t vga_display(char *message, uint16_t line, uint16_t column)
{
	char *vidmem = (char *)VGA_MEMORY;
	uint16_t i = 0;
	uint16_t msg_index = 0;

	i = (line * 80 * 2) + (column * 2);

	while (message[msg_index] != 0)
	{
		if (message[msg_index] == '\n')
		{
			line++;
			column = 0;
			i = (line * 80 * 2) + (column * 2);
			msg_index++;
		}
		else
		{
			// Set content
			vidmem[i] = message[msg_index];
			msg_index++;
			i++;
			// Set color
			vidmem[i] = VGA_COLOR(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
			i++;
		};
	};

	return (msg_index);
}
