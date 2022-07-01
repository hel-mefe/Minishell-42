#include "parsing.h"

char    *ft_strjoin(char *s1, char *s2)
{
    char    *res;
    size_t  len;
    size_t  len1;
    size_t  len2;
    size_t  i;
    size_t  j;

    if (!s1 && s2)
        return (ft_strdup(s2));
    else if (!s2 && s1)
        return (ft_strdup(s1));
    else if (!s1 && !s2)
        return (NULL);
    len1 = ft_strlen(s1);
    len2 = ft_strlen(s2);
    len = len1 + len2;
    res = (char *) malloc ((len + 1) * sizeof(char));
    if (!res)
        return (NULL);
    i = -1;
    while (++i < len1 && s1[i])
        res[i] = s1[i];
    j = 0;
    while (i < len && s2[j])
        res[i++] = s2[j++];
    res[i] = 0;
    return (res);
}

int is_dollar_char_valid(char c)
{
    return (!is_space(c) && (ft_isalnum(c) || c == '_'));
}

char    *get_dollar(char *s)
{
    size_t  i;

    i = 0;
    while (s[i] && is_dollar_char_valid(s[i]))
        i++;
    return (slice(s, 0, i));
}

t_dollar *get_all_dollars(char *s, char **env)
{
    size_t      i;
    t_dollar    *new;
    t_dollar    *head;
    char        *dollar;

    i = 0;
    head = NULL;
    while (s[i])
    {
        if (s[i] == '$' && is_dollar_valid(s + i + 1))
        {
            dollar = get_dollar(s + i + 1);
            i += ft_strlen(dollar);
            new = new_dollar(dollar, get_dollar_val(dollar, env));
            push_back_dollar(&head, new);
        }
        else
            i++;
    }
    return (head);
}

char    *get_dollar_val(char *var, char **env)
{
    size_t  i;
    size_t  len;

    len = ft_strlen(var);
    i = 0;
    while (env[i])
    {
        if (!ft_strncmp(var, env[i], len) && env[i][len] == '=')
            return (slice(env[i], len + 1, ft_strlen(env[i])));
        i++;
    }
    return (slice(var, 0, 0));
}

char    *expand_string(t_dollar *dollars, char **env, int *place, char *s)
{
    size_t  i;
    size_t  j;
    char    *res;
    char    *part;

    res = NULL;
    i = 0;
    j = 0;
    while (s[i])
    {
        if (s[i] == '$' && ft_isdigit(s[i + 1]))
        {
            part = slice(s, j, i);
            res = ft_strjoin(res, part);
            i += 1;
            j = i + 1;
        }
        else if (s[i] == '$' && (ft_isalpha(s[i + 1]) || s[i + 1] == '_'))
        {
            if (j != i)
            {
                part = slice(s, j, i);
                res = ft_strjoin(res, part);
            }
            res = ft_strjoin(res, dollars->val);
            i += ft_strlen(dollars->var);
            j = i + 1;
            dollars = dollars->next;
        }
        else if (s[i] == '$' && s[i + 1] == '?')
        {
            if (j != i)
            {
                part = slice(s, j, i);
                res = ft_strjoin(res, part);
            }
            res = ft_strjoin(res, ft_strdup("*STATUS*"));
            i += 1;
            j = i + 1;
        }
        i++;
    }
    if (i != j)
        res = ft_strjoin(res, slice(s, j, i));
    if (!res[0])
        *place = NONE;
    return (res);
}


// char    *expand_dollar(char *s)
// {
//     t_dollar    *dollars;
//     char        *res;
//     char        *part;
//     size_t      i;
//     size_t      j;

//     dollars = get_all_dollars(s);
//     res = NULL;
//     return ()
//     // i = -1;
//     // j = 0;
//     // while (s[++i])
//     // {
//     //     if (s[i] == '$' && is_dollar_valid(s + i + 1))
//     //     {
//     //         part = slice(s, j, i);
//     //         j = i;
//     //         res = ft_strjoin()
//     //     }
//     // }
// }