int ft_islower(int c)
{
	return (c >= 'a' && c <= 'z');
}

int ft_toupper(int c)
{
	if (ft_islower(c))
		c -= 32;
	return (c);
}

int ft_isupper(int c)
{
	return (c >= 'A' && c <= 'Z');
}

int ft_tolower(int c)
{
	if (ft_isupper(c))
		c += 32;
	return (c);
}

int ft_isprint(int c)
{
	return (c >= 32 && c <= '~');
}

int ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}

int ft_isalpha(int c)
{
	if (ft_isupper(c) || ft_islower(c))
		return (1);
	return (0);
}

int ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}
