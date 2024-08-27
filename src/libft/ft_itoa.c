#include "libft.h"

int ft_itoa(int num, unsigned char *str, int len, int base)
{
	int sum = num;
	int i = 0;
	int digit;

	if (len == 0)
		return -1;
	do
	{
		digit = sum % base;
		if (digit < 10)
			str[i++] = '0' + digit;
		else
			str[i++] = 'A' + digit - 10;
		sum /= base;
	} while (sum && (i < (len - 1)));
	if (i == (len - 1) && sum)
		return -1;
	str[i] = '\0';
	ft_strrev(str);
	return 0;
}
