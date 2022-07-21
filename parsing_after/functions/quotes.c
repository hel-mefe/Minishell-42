#include "../parsing.h"

int is_singly(char c)
{
    return (c == '\'');
}

int is_doubly(char c)
{
    return (c == '\"');
}

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

void    mark_breaking_quotes(char *s)
{
    size_t  i;
    char    c;
    char    opposite;

    c = 0;
    i = 0;
    while (s[i])
    {
        if (c == 0 && (s[i] == '\'' || s[i] == '\"'))
        {
            c = s[i];
            s[i] = BREAKING_POINT;
        }
        else if (c && s[i] == c)
        {
            if (search_for_char(s + i + 1, opposite, c) || (s[i] == '\"' && s[i + 1] == '\"'))
                s[i] = BREAKING_POINT;
            else if (!search_for_char(s + i + 1, c, 0))
                s[i] = BREAKING_POINT;
            else if (!s[i + 1] || is_space(s[i + 1]) || is_token(s[i + 1]))
                s[i] = BREAKING_POINT;
            c = 0;
        }
        if (c == '\'')
            opposite = '\"';
        else
            opposite = '\'';
        i++;
    }
}
