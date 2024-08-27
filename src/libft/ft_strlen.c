#include "libft.h"

uint32_t ft_strlen(char const *s)
{
	uint32_t i;
	i = 0;
	while (s[i])
	{
		i += 1;
	}
	return i;
}
