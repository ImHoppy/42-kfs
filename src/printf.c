#include "vga.h"
#include "libft/libft.h"
#include <stdarg.h>

uint16_t printf(uint8_t line, const char format[], ...)
{
	va_list args;
	va_start(args, format);
	unsigned int column = 0;
	unsigned int colors = VGA_COLOR(VGA_COLOR_WHITE, VGA_COLOR_BLACK);

	while (*format != 0)
	{
		if (*format == '~')
		{
			format++;
			switch (*format)
			{
			case 'r':
				colors = VGA_COLOR(VGA_COLOR_LIGHT_RED, VGA_COLOR_BLACK);
				break;
			case 's':
				colors = VGA_COLOR(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
				break;
			case 'b':
				colors = VGA_COLOR(VGA_COLOR_LIGHT_BLUE, VGA_COLOR_BLACK);
				break;
			case 'g':
				colors = VGA_COLOR(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
				break;
			}
		}
		else if (*format == '%')
		{
			format++;
			switch (*format)
			{
			case 'c':
			{
				char c = va_arg(args, int);
				char str[2];
				str[0] = c;
				str[1] = 0;
				column += vga_display_color(str, line, column, colors);
				break;
			}
			case 's':
			{
				char *str = va_arg(args, char *);
				column += vga_display_color(str, line, column, colors);
				break;
			}
			case 'd':
			{
				int num = va_arg(args, int);
				char str[32];
				ft_itoa(num, str, 32, 10);
				column += vga_display_color(str, line, column, colors);
				break;
			}
			case 'x':
			{
				int num = va_arg(args, int);
				char str[32];
				ft_itoa(num, str, 32, 16);
				column += vga_display_color("0x", line, column, colors);
				column += vga_display_color(str, line, column, colors);
				break;
			}
			}
		}
		else
		{
			char str[2];
			str[0] = *format;
			str[1] = 0;
			column += vga_display_color(str, line, column, colors);
		}
		format++;
	}
	return column;
}
