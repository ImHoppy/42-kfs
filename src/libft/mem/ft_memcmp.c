#include "../libft.h"

int ft_memcmp(const void *s1, const void *s2, unsigned int n)
{
	unsigned char *str_s1;
	unsigned char *str_s2;
	unsigned int i;

	str_s1 = (unsigned char *)s1;
	str_s2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (str_s1[i] != str_s2[i])
			return (str_s1[i] - str_s2[i]);
		i++;
	}
	return (0);
}
