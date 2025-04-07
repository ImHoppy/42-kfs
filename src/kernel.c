#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "vga.h"
#include "io.h"
#include "kernel.h"
#include "libft/libft.h"
#include "keyboard.h"
#include "gdt/gdt.h"

#define SCREEN_HEIGHT VGA_HEIGHT * 2
#define PROMPT "~bprompt>~s "
#define PROMPT_LEN 8

#define MAX_LINE 64

typedef struct
{
	char data[SCREEN_HEIGHT + 1][VGA_WIDTH];
	uint8_t last_line;
	char line[MAX_LINE + 1];
	uint8_t cursor_x;
	uint8_t len;
	uint8_t scroll;
} screen_t;

#define MAX_SCREEN 3
screen_t screens[MAX_SCREEN] = {0};
uint8_t current_screen = 0;

void draw_screen()
{
	screen_t *screen = &screens[current_screen];
	int last_displayed = screen->last_line - screen->scroll;

	for (uint8_t i = VGA_HEIGHT - 2; i > 0; i--)
	{
		vga_clear_line(i);
		char *to_draw = NULL;
		for (int j = last_displayed - 1; j >= 0; j--)
		{
			if (screen->data[j][0] != 0)
			{
				to_draw = screen->data[j];
				last_displayed = j;
				break;
			}
		}
		if (to_draw)
			printf(i, "%s ", to_draw);
		printf(0, "Screen n*~g%d~s, Scroll: ~r%d   ", current_screen, screen->scroll);
	}
}

void reset_prompt()
{
	vga_clear_line(VGA_HEIGHT - 1);
	printf(VGA_HEIGHT - 1, PROMPT "%s ", screens[current_screen].line);
	vga_set_cursor(VGA_HEIGHT - 1, PROMPT_LEN + screens[current_screen].cursor_x);
}

/* Entry point */
void kmain()
{
	init_gdt();
	vga_clear_screen();

	uint8_t last_key = 0;
	uint8_t key = 0;

	printf(0, "42\n");
	reset_prompt();
	while (42)
	{
		key = keyboard_read();
		uint8_t scancode = intb(KEYBOARD_DATA_PORT);
		screen_t *screen = &screens[current_screen];

		if (scancode & RELEASED_MASK)
		{
			last_key = 0;
		}
		else if (key > 0 && key != last_key)
		{
			if (screen->len < MAX_LINE && ft_isprint(key))
			{
				if (screen->cursor_x < screen->len)
				{
					ft_memmove(screen->line + screen->cursor_x + 1, screen->line + screen->cursor_x, screen->len - screen->cursor_x);
					screen->line[screen->cursor_x] = key;
				}
				else
				{
					screen->line[screen->len] = key;
				}
				screen->len++;
				screen->cursor_x++;
				reset_prompt();
			}
			switch (key)
			{
			case 128: // UP
				screen->scroll++;
				draw_screen();
				break;
			case 131: // DOWN
				screen->scroll--;
				draw_screen();
				break;
			case 129: // left
				if (screen->cursor_x > 0)
					screen->cursor_x--;
				vga_set_cursor(VGA_HEIGHT - 1, PROMPT_LEN + screen->cursor_x);
				break;
			case 130: // right
				if (screen->cursor_x < screen->len)
					screen->cursor_x++;
				vga_set_cursor(VGA_HEIGHT - 1, PROMPT_LEN + screen->cursor_x);
				break;
			case '\n':
				if (screen->len > 0)
				{
					ft_memcpy(screen->data[screen->last_line], screen->line, screen->len);
					ft_memset(screen->line, 0, screen->len);
					screen->cursor_x = 0;
					screen->len = 0;
					screen->scroll = 0;
					screen->last_line++;
					draw_screen();
					reset_prompt();
				}
				break;
			case '\b':
				if (screen->cursor_x <= 0)
					break;
				screen->cursor_x--;
				ft_memmove(screen->line + screen->cursor_x, screen->line + screen->cursor_x + 1, screen->len - screen->cursor_x);
				screen->len--;
				reset_prompt();
				break;
			case 132:
				current_screen = (current_screen + 1) % MAX_SCREEN;
				draw_screen();
				reset_prompt();
				break;
			case 133:
				if (current_screen == 0)
					current_screen = MAX_SCREEN - 1;
				else
					current_screen--;
				draw_screen();
				reset_prompt();
				break;
			default:
				break;
			}
			last_key = key;
		}
	}
}
