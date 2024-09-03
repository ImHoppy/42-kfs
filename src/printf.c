#include "vga.h"
#include "libft/libft.h"
#include <stdarg.h>

uint16_t printf(const char format[], ...)
{
	va_list args;
	va_start(args, format);
	unsigned int column = 0;

	while (*format != 0)
	{
		if (*format == '%')
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
				column += vga_display(str, 0, column);
				break;
			}
			case 's':
			{
				char *str = va_arg(args, char *);
				column += vga_display(str, 0, column);
				break;
			}
			case 'd':
			{
				int num = va_arg(args, int);
				char str[32];
				ft_itoa(num, str, 32, 10);
				column += vga_display(str, 0, column);
				break;
			}
			case 'x':
			{
				int num = va_arg(args, int);
				char str[32];
				ft_itoa(num, str, 32, 16);
				column += vga_display("0x", 0, column);
				column += vga_display(str, 0, column);
				break;
			}
			}
		}
		else
		{
			char str[2];
			str[0] = *format;
			str[1] = 0;
			column += vga_display(str, 0, column);
		}
		format++;
	}
	return column;
}
