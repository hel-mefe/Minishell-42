#include "../../include/parsing.h"

int search_for_char(char *s, char c, char end)
{
    size_t  i;

    i = 0;
    while (s[i] && s[i] != end)
    {
        if (s[i] == c)
            return (1);
        i++;
    }
    return (0);
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
