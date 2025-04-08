#include "libft.h"

static int	ft_isspace(int c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int		negative;
	long	result;
	int		i;

	if (str == NULL)
		return (0);
	i = 0;
	result = 0;
	negative = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
		negative = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] != '\0' && ft_isdigit(str[i]))
	{
		result = result * 10 + (str[i] - '0');
		if (result < 0 && negative == -1)
			return (0);
		if (result > 2147483647 && negative == 1)
			return (-1);
		i++;
	}
	return (result * negative);
}