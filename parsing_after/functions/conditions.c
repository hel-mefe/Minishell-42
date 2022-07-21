# include "../parsing.h"

int is_token(char c)
{
    return (c == '<' || c == '|' || c == '>');
}

int is_space(char c)
{
    return (c == ' ' || c == '\n' || c == '\v' || c == '\r' || c == '\t' || c == '\f');
}

int ft_isalpha(char c)
{
    return ((c >= 'a' && c <= 'z') || (c <= 'Z' && c >= 'A'));
}

int ft_isdigit(char c)
{
    return (c >= '0' && c <= '9');
}

int ft_isalnum(char c)
{
    return (ft_isalpha(c) || ft_isdigit(c));
}