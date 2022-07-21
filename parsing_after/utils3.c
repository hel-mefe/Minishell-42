#include "parsing.h"

int is_syntax_token(char c)
{
    return (c == '|' || c == '<' || c == '>');
}


int in_string(char *s, char c)
{
    size_t  i;

    i = -1;
    while (s[++i])
    {
        if (s[i] == c)
            return (1);
    }
    return (0);
}

char	*remove_quotes(char *s)
{
	size_t	i;
	size_t	a;
	size_t	b;
	char	*res;
	char	c;

    if (!s)
        return (NULL);
    res = 0;
    mark_breaking_quotes(s);
    i = 0;
    a = 0;
    while (s[i])
    {
        if (s[i] == BREAKING_POINT)
        {
            res = ft_strjoin_free(res, slice(s, a, i));
            a = i + 1;
        }
        i++;
    }
    if (i > a)
        res = ft_strjoin_free(res, slice(s, a, i));
    free(s);
    return (res);
}

char    *remove_chars(char *s, char *r)
{
    size_t  i;
    size_t  j;
    char    *res;

    res = slice(s, 0, 0);
    j = 0;
    i = 0;
    while (s[i])
    {
        if (in_string(r, s[i]))
        {
            if (i != 0)
                res = ft_strjoin(res, slice(s, j, i));
            while (s[i] && in_string(r, s[i]))
                i++;
            j = i;
        }
        else
            i++;
    }
    if (i != j)
        res = ft_strjoin(res, slice(s, j, i));
    return (res);
}

// char    *remove_char(char *s, char c)
// {
//     size_t  i;
//     size_t  j;
//     char    *res;

//     res = NULL;
//     j = 0;
//     i = 0;
//     while (s[i])
//     {
//         if (s[i] == c)
//         {
//             res = ft_strjoin(res, slice(s, j, i));
//             while (s[i] == c)
//                 i++;
//             j = i;
//         }
//         else
//             i++;
//     }
//     return (res);
// }