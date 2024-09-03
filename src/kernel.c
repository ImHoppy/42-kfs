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

	printf("42\n");
	while (42)
	{
		key = keyboard_read();
		if (key != last_key)
		{
			printf("%c ", key);
			last_key = key;
		}
	}
}
