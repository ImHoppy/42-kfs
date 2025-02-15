#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "vga.h"
#include "io.h"
#include "kernel.h"
#include "libft/libft.h"
#include "keyboard.h"

#define SCREEN_HEIGHT VGA_HEIGHT * 2
#define PROMPT "~bprompt>~s "
#define PROMPT_LEN 8

uint8_t screen[SCREEN_HEIGHT + 1][VGA_WIDTH] = {0};
uint8_t scroll = 0;
uint8_t last_line = 0;

void draw_screen()
{
	int last_displayed = last_line - scroll;
	for (uint8_t i = VGA_HEIGHT - 2; i > 0; i--)
	{
		vga_clear_line(i);
		char *to_draw = NULL;
		for (int j = last_displayed; j >= 0; j--)
		{
			if (screen[j][0] != 0)
			{
				to_draw = screen[j];
				last_displayed = j - 1;
				break;
			}
		}
		if (to_draw)
			printf(i, "%s ", to_draw);
		printf(0, "%d ", scroll);
	}
}

void reset_prompt()
{
	vga_clear_line(VGA_HEIGHT - 1);
	printf(VGA_HEIGHT - 1, PROMPT);
	vga_set_cursor(VGA_HEIGHT - 1, PROMPT_LEN);
}

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
	reset_prompt();
	while (42)
	{
		key = keyboard_read();
		uint8_t scancode = intb(KEYBOARD_DATA_PORT);
		if (scancode & RELEASED_MASK)
		{
			last_key = 0;
		}
		else if (key > 0 && key != last_key)
		{
			if (len < (64 - 1) && ft_isprint(key))
			{
				line[len] = key;
				len++;
				printf(VGA_HEIGHT - 1, PROMPT "%s", line);
				cursor_x++;
				vga_set_cursor(VGA_HEIGHT - 1, PROMPT_LEN + cursor_x);
			}
			switch (key)
			{
			case 128: // UP
				scroll++;
				draw_screen();
				break;
			case 131: // DOWN
				scroll--;
				draw_screen();
				break;
			case 129: // left
				if (cursor_x > 0)
					cursor_x--;
				vga_set_cursor(VGA_HEIGHT - 1, PROMPT_LEN + cursor_x);
				break;
			case 130: // right
				if (cursor_x < len)
					cursor_x++;
				vga_set_cursor(VGA_HEIGHT - 1, PROMPT_LEN + cursor_x);
				break;
			case '\n':
				if (len > 0)
				{
					ft_memcpy(screen[last_line], line, len);
					last_line++;
					ft_memset(line, 0, len);
					cursor_x = 0;
					len = 0;
					draw_screen();
					reset_prompt();
				}
				break;
			default:
				break;
			}
			last_key = key;
		}
	}
}
