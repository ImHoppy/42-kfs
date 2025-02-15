#include "../libft.h"

void *ft_memset(void *b, int c, unsigned int len)
{
	unsigned int i;
	unsigned char *a;

	i = 0;
	a = (unsigned char *)b;
	while (i < len)
		a[i++] = (unsigned char)c;
	b = (void *)a;
	return (b);
}
