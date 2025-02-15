#include "../libft.h"

void *ft_memmove(void *dst, const void *src, unsigned int len)
{
	unsigned char *temp_dst;
	unsigned char *temp_src;
	unsigned int i;

	temp_dst = (unsigned char *)dst;
	temp_src = (unsigned char *)src;
	i = 0;
	if (dst == NULL && src == NULL)
		return (NULL);
	while (i < len)
	{
		if (dst > src)
		{
			len--;
			temp_dst[len] = temp_src[len];
		}
		else
		{
			temp_dst[i] = temp_src[i];
			i++;
		}
	}
	return (dst);
}
