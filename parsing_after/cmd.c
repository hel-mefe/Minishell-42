#include "parsing.h"

size_t  get_quote_end(char *s, char c)
{
    size_t  i;
    int     end;

    end = -1;
    i = 0;
    while (s[i])
    {
        if (s[i] == c)
            end = i;
        if (s[i] == c && (!s[i + 1] || is_space(s[i + 1]) || s[i + 1] == '|'))
            break ;
        i++;
    }
    return (end);
}

t_cmd   *get_commands(t_data *data, char *s)
{
    size_t  i;
    size_t  j;
    t_cmd   *head;
    t_cmd   *new;
    char    *cmd;

    head = NULL;
    i = -1;
    j = 0;
    while (s[++i])
    {
        if (s[i] == '\'')
            i += get_quote_end(s + i + 1, '\'') + 1;
        else if (s[i] == '\"')
            i += get_quote_end(s + i + 1, '\"') + 1;
        if (s[i] == '|' || !s[i + 1])
        {
            new = new_command(head);
            if (!s[i + 1])
                new->line = slice(s, j, i + 1);
            else
                new->line = slice(s, j, i);
            push_command(&head, new);
            j = i + 1;
            while (is_space(s[j])) // Newly Added
                j++;
            i = j;
        }
    }
    return (head);
}
