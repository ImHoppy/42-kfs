#ifndef LIBFT
#define LIBFT

#include <stdint.h>

int ft_itoa(int num, unsigned char *str, int len, int base);

/// string

uint32_t ft_strlen(char const *s);
void ft_strrev(unsigned char *str);

/// char
static int ft_islower(int c);
int ft_toupper(int c);
static int ft_isupper(int c);
int ft_tolower(int c);
int ft_isprint(int c);
int ft_isdigit(int c);
int ft_isascii(int c);
int ft_isalpha(int c);
int ft_isalnum(int c);

#endif
