
static int char_to_hex(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';
    if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;
    if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;
    return -1;
}

int ft_hextoint(const char *str)
{
    if (!str)
        return 0;

    if (str[0] == '0' && str[1] == 'x')
    {
        str += 2;
    }

    int result = 0;
    while (*str)
    {
        int hex = char_to_hex(*str);
        if (hex == -1)
            break;
        result = (result << 4) | hex;

        str++;
    }
    return result;
}