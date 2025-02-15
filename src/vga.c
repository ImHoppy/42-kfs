#include "vga.h"
#include "io.h"

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
	return vga_display_color(message, line, column, VGA_COLOR(VGA_COLOR_WHITE, VGA_COLOR_BLACK));
}

uint16_t vga_display_color(char *message, uint16_t line, uint16_t column, uint8_t color)
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
			vidmem[i] = color;
			i++;
		};
	};

	return (msg_index);
}

void vga_set_cursor(uint8_t row, uint8_t col)
{
	uint16_t pos = row * VGA_WIDTH + col;

	outb(VGA_INDEX_REG, 0x0F);
	outb(VGA_DATA_REG, (uint8_t)(pos & 0xFF));

	outb(VGA_INDEX_REG, 0x0E);
	outb(VGA_DATA_REG, (uint8_t)((pos >> 8) & 0xFF));
}
