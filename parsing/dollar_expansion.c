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

char    *ft_strjoin_free(char *s1, char *s2)
{
    char    *res;
    size_t  len;
    size_t  len1;
    size_t  len2;
    size_t  i;
    size_t  j;

    if (!s1 && s2)
        return (s2);
    else if (!s2 && s1)
        return (s1);
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
    if (s1)
        free(s1);
    if (s2)
        free(s2);
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

t_dollar *get_all_dollars(char *s, char **env, t_env *main_env)
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
            new = new_dollar(dollar, get_dollar_val(dollar, env, main_env));
            push_back_dollar(&head, new);
        }
        else
            i++;
    }
    return (head);
}

char    *get_dollar_val(char *var, char **env, t_env *main_env)
{
    size_t  i;
    size_t  len;

    len = ft_strlen(var);
    i = 0;
    while (main_env)
    {
        if (!ft_strcmp(var, main_env->name))
            return (ft_strdup(main_env->data));
        main_env = main_env->next;
    }
    return (slice(var, 0, 0));
}

char    *expand_string(t_dollar *dollars, char **env, int *place, char *s)
{
    size_t  i;
    size_t  j;
    char    *res;
    char    *part;
    char    *k_res;
    int     singly;

    singly = 0;
    res = NULL;
    i = 0;
    j = 0;
    while (s[i])
    {
        if (s[i] == '\'')
            singly = !singly;
        if (s[i] == '$' && ft_isdigit(s[i + 1]) && !singly)
        {
            k_res = res;
            part = slice(s, j, i);
            res = ft_strjoin_free(res, part);
            // if (k_res)
            //     free(k_res);
            i += 1;
            j = i + 1;
        }
        else if (s[i] == '$' && (ft_isalpha(s[i + 1]) || s[i + 1] == '_') && !singly)
        {
            if (j != i)
            {
                k_res = part;
                part = slice(s, j, i);
                res = ft_strjoin_free(res, part);
                // free(part);
                // if (k_res)
                //     free(k_res);
            }
            k_res = res;
            res = ft_strjoin(res, dollars->val);
            i += ft_strlen(dollars->var);
            j = i + 1;
            dollars = dollars->next;
            if (k_res)
                free(k_res);
        }
        else if (s[i] == '$' && s[i + 1] == '?' && !singly)
        {
            if (j != i)
            {
                k_res = res;
                part = slice(s, j, i);
                res = ft_strjoin_free(res, part);
                // if (k_res)
                //     free(k_res);
                // free(part);
            }
            // k_res = res;
            part = ft_itoa(get_nb_status);
            res = ft_strjoin_free(res, part);
            // if (k_res)
            //     free(k_res);
            i += 1;
            j = i + 1;
        }
        i++;
    }
    if (i != j)
    {
        // k_res = res;
        part = slice(s, j, i);
        res = ft_strjoin_free(res, part);
        // if (k_res)
        //     free(k_res);
    }
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