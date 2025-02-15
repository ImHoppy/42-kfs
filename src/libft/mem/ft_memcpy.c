#include "../libft.h"

void *ft_memcpy(void *dst, const void *src, unsigned int n)
{
	unsigned char *temp_dst;
	unsigned char *temp_src;

	if (dst == NULL && src == NULL)
		return (NULL);
	temp_dst = (unsigned char *)dst;
	temp_src = (unsigned char *)src;
	while (n > 0)
	{
		*temp_dst++ = *temp_src++;
		n--;
	}
	return (dst);
}
