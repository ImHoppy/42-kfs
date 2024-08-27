#include "libft.h"

void ft_strrev(unsigned char *str)
{
	int i;
	int j;
	unsigned char a;
	unsigned len = ft_strlen((const char *)str);
	for (i = 0, j = len - 1; i < j; i++, j--)
	{
		a = str[i];
		str[i] = str[j];
		str[j] = a;
	}
}
