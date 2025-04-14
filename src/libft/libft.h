#ifndef LIBFT
#define LIBFT

#include <stdint.h>
#include <stddef.h>

int ft_itoa(unsigned int num, char *str, int len, int base);

/// string

uint32_t ft_strlen(char const *s);
void ft_strrev(char *str);
int	ft_strcmp(const char *s1, const char *s2);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
int ft_hextoint(const char *str);

/// char
int ft_islower(int c);
int ft_toupper(int c);
int ft_isupper(int c);
int ft_tolower(int c);
int ft_isprint(int c);
int ft_isdigit(int c);
int ft_isascii(int c);
int ft_isalpha(int c);
int ft_isalnum(int c);

int	ft_atoi(const char *str);

/// mem
void *ft_memcpy(void *dst, const void *src, unsigned int n);
void *ft_memset(void *b, int c, unsigned int len);
void *ft_memmove(void *dst, const void *src, unsigned int len);
int ft_memcmp(const void *s1, const void *s2, unsigned int n);
void *ft_memchr(const void *s, int c, unsigned int n);

#endif
